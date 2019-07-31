#include "stdafx.h"
#include "SICKLaserScanner.h"
#include "comm\SockTcp.h"
#include <sstream>

#define MAX_TIMEOUT 5000	// ms
#define TIMEOUT_OS_ERROR 20	// ms
#define TIMEOUT_SAFTY 1		// ms

using namespace sensor;
using namespace eventManager;
using namespace std;

// Overriding Function
CSICKLaserScanner::CSICKLaserScanner(string sensorName, eSICKLaserScannerModel model, string ip, int port, bool upsideDown)
	:CSensorModule(sensorName){
	m_cpIP = new char[16];
	m_client = new CSockTcp();

	// 매개변수
	if (setModel(model) != RETURN_NON_ERROR || setIP(ip) != RETURN_NON_ERROR || setPort(port) ||
		setUpsideDown(upsideDown) != RETURN_NON_ERROR);

	// 모델별 파라미터 설정
	switch (m_eModel) {
	case eSICKLaserScannerModel::LMS1xx:
		m_nFreqency = 25;
		m_nAngleResolution = 4;
		m_nStartAngle = -45;
		m_nEndAngle = 225;
		break;
	case eSICKLaserScannerModel::TiMxxx:
		m_nFreqency = 15;
		m_nAngleResolution = 3;
		m_nStartAngle = -45;
		m_nEndAngle = 225;
		break;
	default:
		
		return;
	}
	int a = (1000 / m_nFreqency) + TIMEOUT_OS_ERROR + TIMEOUT_SAFTY;
	setThreadPeriod(a);
	setDataTimeout(a);
	m_nConnectionTimeout = 100;
}

CSICKLaserScanner::~CSICKLaserScanner() {
	Disconnect();
	while (getStatus() != STATE_INIT);
	SAFE_DELETE(m_cpIP);
	SAFE_DELETE(m_client);
}
int CSICKLaserScanner::ConnectAct() {
	// Communication specification
	m_client->Init(m_cpIP, m_nPort);
	// Socket open
	if (!m_client->OpenClient())
		return RETURN_FAILED;
	// Socket Connect (non-Blocking function)
	if (!m_client->Connect(m_nConnectionTimeout)) {
		m_client->Close();
		return RETURN_FAILED;
	}
	m_client->SetTimeout(m_nDataTimeout);
	// Data structure setting
	SetLaserScanData();
	// Device Init
	if(DeviceInitialize() != RETURN_NON_ERROR)
		return RETURN_FAILED;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::ResetAct() {
	if (!m_client->IsValidHandle())
		DisconnectAct();
	return ConnectAct();
}
int CSICKLaserScanner::UpdateData() {
	int nDataLength;
	if (AcquireData(&nDataLength) != RETURN_NON_ERROR)
		return RETURN_FAILED;
	if (DecodeScanDataAll_LMS100(nDataLength) != RETURN_NON_ERROR)
		return RETURN_FAILED;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::DisconnectAct() {
	m_client->Close();
	return RETURN_NON_ERROR;
}

// Getter & Setter
int CSICKLaserScanner::getData(LaserScanData * scandata) {
	// Switching Double Buffer
	if (m_bBufferSwitch)
		memcpy(scandata, &m_bufferA, sizeof(m_bufferA));
	else 
		memcpy(scandata, &m_bufferB, sizeof(m_bufferB));
	/*
	if (m_bBufferSwitch) {
		scandata = new LaserScanData();
		scandata->data_len = getResolDeg()*(m_bufferA.end_angle - m_bufferA.start_angle);
		scandata->dist = new UINT16[scandata->data_len];
		scandata->rssi = new UINT16[scandata->data_len];
		for (int i = 0; i < scandata->data_len; i++) {
			scandata->dist[i] = m_bufferA.dist[int(getResolDeg()*(m_bufferA.start_angle) + i)];
			scandata->rssi[i] = m_bufferA.rssi[int(getResolDeg()*(m_bufferA.start_angle) + i)];
		}
	}
	else {
		scandata = new LaserScanData();
		scandata->data_len = getResolDeg()*(m_bufferB.end_angle - m_bufferB.start_angle);
		scandata->dist = new UINT16[scandata->data_len];
		scandata->rssi = new UINT16[scandata->data_len];
		for (int i = 0; i < scandata->data_len; i++) {
			scandata->dist[i] = m_bufferB.dist[int(getResolDeg()*(m_bufferB.start_angle) + i)];
			scandata->rssi[i] = m_bufferB.rssi[int(getResolDeg()*(m_bufferB.start_angle) + i)];
		}
	}
	*/
	m_bBufferSwitch = !m_bBufferSwitch;
	return true;
}
int CSICKLaserScanner::getModel() { return m_eModel; }
int CSICKLaserScanner::getFreqency() { return m_nFreqency; }
int CSICKLaserScanner::getAngleResolution() { return m_nAngleResolution; }
int CSICKLaserScanner::getStartAngle() { return m_nStartAngle; }
int CSICKLaserScanner::getEndAngle() { return m_nEndAngle; }
bool CSICKLaserScanner::getUpsideDown() { return m_bUpsideDown; }
int CSICKLaserScanner::getConnectionTimeout(){ return m_nConnectionTimeout; }
int CSICKLaserScanner::getDataTimeout() { return m_nDataTimeout; }
string CSICKLaserScanner::getIP() { return string(m_cpIP); }
int CSICKLaserScanner::getPort() { return m_nPort; }
int CSICKLaserScanner::setModel(int model) {
	m_eModel = (eSICKLaserScannerModel)model;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::setIP(string ip) {
	string strSub = ip;
	for (int i = 0; i < 3; i++) {
		int tokenLength = strSub.find(".");
		if (tokenLength > 0) {
			int tokenNum = atoi(strSub.substr(0, strSub.find(".")).c_str());
			if (tokenNum < 0 || tokenNum > 255)
			{
				//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LASER_INVALID_PARAMETER, true, true);
				return RETURN_NON_ERROR;
			}

			strSub = strSub.substr(strSub.find(".") + 1, strSub.size());
		}
		else
		{
			//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LASER_INVALID_PARAMETER, true, true);
			return RETURN_NON_ERROR;
		}
	}
	int tokenNum = atoi(strSub.c_str());
	if (tokenNum < 0 || tokenNum > 255)
	{
		//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LASER_INVALID_PARAMETER, true, true);
		return RETURN_NON_ERROR;
	}

	//_DEPRECATE_UNCHECKED(copy, m_cpIP);
	copy(ip.begin(), ip.end(), m_cpIP);
	m_cpIP[ip.length()] = '\0';
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::setPort(int nPort) {
	if (nPort < 0 || nPort > 65535)
	{
		//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LASER_INVALID_PARAMETER, true, true);
		return RETURN_NON_ERROR;
	}
	m_nPort = nPort;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::setConnectionTimeout(int nTimeout) {
	if (nTimeout < 0 || nTimeout > MAX_TIMEOUT)
	{
		//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LASER_INVALID_PARAMETER, true, true);
		return RETURN_NON_ERROR;
	}
	m_nConnectionTimeout = nTimeout;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::setDataTimeout(int nTimeout) {
	if (nTimeout < 0)
		return RETURN_NON_ERROR;
	if (nTimeout > MAX_TIMEOUT)
		//g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_TIMEOUT_IS_LARGE, true, false);
	m_nDataTimeout = nTimeout;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::setFreqency(int freq) {
	// 모델별 파라미터 설정
	switch (m_eModel) {
	case eSICKLaserScannerModel::LMS1xx:
		if (freq != 25 || freq != 50)
		{
			//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LASER_INVALID_PARAMETER, true, true);
			return RETURN_NON_ERROR;
		}
		break;
	case eSICKLaserScannerModel::TiMxxx:
		if (freq != 15)
		{
			//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LASER_INVALID_PARAMETER, true, true);
			return RETURN_NON_ERROR;
		}
		break;
	}
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::setAngleResolution(int resol) {
	// 모델별 파라미터 설정
	switch (m_eModel) {
	case eSICKLaserScannerModel::LMS1xx:
		if (resol != 4|| resol != 2)
		{
			g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_ANGLE_RESOLUTION, true, false);
			return RETURN_FAILED;
		}
		break;
	case eSICKLaserScannerModel::TiMxxx:
		if (resol != 3 || resol != 1)
		{
			g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_ANGLE_RESOLUTION, true, false);
			return RETURN_FAILED;
		}
		break;
	}
	m_nAngleResolution = resol;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::setStartAngle(int angle) {
	if (angle < -45 || angle > 225 || angle > m_nEndAngle)
	{
		//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LASER_INVALID_PARAMETER, true, true);
		return RETURN_NON_ERROR;
	}
	m_nStartAngle = angle;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::setEndAngle(int angle) {
	if (angle < -45 || angle > 225 || angle < m_nStartAngle) 
	{
		//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LASER_INVALID_PARAMETER, true, true);
		return RETURN_NON_ERROR;
	}
	m_nEndAngle = angle;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::setUpsideDown(bool upsideDown) {
	m_bUpsideDown = upsideDown;
	return RETURN_NON_ERROR;
}

// private
void CSICKLaserScanner::SetLaserScanData() {
	m_bufferA.nData_len = m_bufferB.nData_len = int(getAngleResolution() * (225+45)) + 1;
	m_bufferA.nAngleResolution = m_bufferB.nAngleResolution = m_nAngleResolution;
	m_bufferA.nStart_angle = m_bufferB.nStart_angle = m_nStartAngle;
	m_bufferA.nEnd_angle = m_bufferB.nEnd_angle = m_nEndAngle;
	m_bufferA.dist = new UINT16[m_bufferA.nData_len];
	m_bufferB.dist = new UINT16[m_bufferB.nData_len];
	m_bufferA.rssi = new UINT16[m_bufferA.nData_len];
	m_bufferB.rssi = new UINT16[m_bufferB.nData_len];
	m_nResSize=m_bufferA.nData_len * 10 + 20;	// 10 = DIST 1~5 + RSSI 1~5 ,20 = telegram header
	m_res = new unsigned char[m_nResSize]; 
}
int CSICKLaserScanner::DeviceInitialize()
{
	// Login
	Send("\02sMN SetAccessMode 02 B21ACE26\03");
	if (m_client->Recv(m_res, m_nResSize) <= 0)
		return RETURN_FAILED;
	else
	{
		if (strncmp((char*)m_res, "\02sFA", 4) == 0);
			//g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_NAV_MODE_CHANGE_ERROR, true, false);
	}
	// Configure scandata content
	Send("\02sWN LMDscandatacfg 01 00 1 1 0 00 00 1 0 0 0 +1\03");
	if (m_client->Recv(m_res, m_nResSize) <= 0) {
		if (m_res[0] == '\02' && m_res[1] == 's'&&m_res[2] == 'F'&&m_res[3] == 'A')
			return RETURN_FAILED;
	}
	// Start measurement
	Send("\02sMN LMCstartmeas\03");
	if (m_client->Recv(m_res, m_nResSize) <= 0) {
		if (m_res[0] == '\02' && m_res[1] == 's'&&m_res[2] == 'F'&&m_res[3] == 'A')
			return RETURN_FAILED;
	}
	// Set to run
	Send("\02sMN Run\03");
	if (m_client->Recv(m_res, m_nResSize) <= 0) {
		if (m_res[0] == '\02' && m_res[1] == 's'&&m_res[2] == 'F'&&m_res[3] == 'A')
			return RETURN_FAILED;
	}
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::Send(string cmd) {
	if (m_client->Send((unsigned char *)(cmd.c_str()), cmd.size()) != cmd.size())
		return RETURN_FAILED;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::Recv(unsigned char ** data, int * lenth) {
	int n_res = m_client->Recv(m_res, sizeof(m_res));
	if (n_res <= 0)
		return RETURN_FAILED;
	*data = new unsigned char[n_res];
	*lenth = n_res;
	memcpy(*data, m_res, n_res);
	return RETURN_NON_ERROR;
}
string CSICKLaserScanner::DecToHexString(int dec) {
	stringstream my_ss;
	my_ss << hex << dec;
	return my_ss.str();
}
string CSICKLaserScanner::IntToString(int nInt) {
	if (nInt >= 0)
		return "+"+to_string(nInt);
	else
		return to_string(nInt);
}
int CSICKLaserScanner::AcquireData(int * len) {
	Send("\02sRN LMDscandata\03");
	int n_res = m_client->Recv(m_res, m_nResSize);
	if (n_res <= 0)
		return RETURN_FAILED;
	if ((m_res[0] != 0x02) || (m_res[n_res - 1] != 0x03))
		return RETURN_FAILED;
	*len = n_res;
	return RETURN_NON_ERROR;
}
int CSICKLaserScanner::DecodeScanDataAll_LMS100(int datanum)
{
	int stat = 0;
	int scanCount = 0, scanCount1 = 0;
	bool decodeend = false;

	int start_index = 0;
	int size_index = 0;

	char * tok = strtok((char *)m_res + 1, " "); // skip <STX>

	if (strncmp(tok, "sRA", 3) != 0)
		return RETURN_FAILED;

	tok = strtok(NULL, " "); //Command
	if (strncmp(tok, "LMDscandata", 11) != 0)
		return RETURN_FAILED;
	tok = strtok(NULL, " "); //VersionNumber
	tok = strtok(NULL, " "); //DeviceNumber
	tok = strtok(NULL, " "); //Serial number
	tok = strtok(NULL, " "); //DeviceStatus0
	tok = strtok(NULL, " "); //DeviceStatus1
							 //Counter starting with first measured value after reaching the highest number
	tok = strtok(NULL, " "); //TelegramCounter
	tok = strtok(NULL, " "); //ScanCounter
	//Counting the time since power up thedevice; starting with 0. In the output telegram this is the time at
	//the zero index (- 14°) before the measurement itself starts.
	tok = strtok(NULL, " "); //TimeSinceStartup
	//Time in μs when the complete scan is transmitted to the buffer for data output; starting with 0 at scanner boot up.
	tok = strtok(NULL, " "); //TransmissionDuration
	tok = strtok(NULL, " "); //InputStatus0
	tok = strtok(NULL, " "); //InputStatus1
	tok = strtok(NULL, " "); //OutputStatus0
	tok = strtok(NULL, " "); //OutputStatus1
	tok = strtok(NULL, " "); //ReservedByteA
	tok = strtok(NULL, " "); //ScanningFrequency
	tok = strtok(NULL, " "); //MeasurementFrequency
	tok = strtok(NULL, " "); //NumberEncoders
	int NumberEncoders;
	std::sscanf(tok, "%d", &NumberEncoders);
	for (int i = 0; i < NumberEncoders; i++) {
		tok = strtok(NULL, " "); //EncoderPosition
		tok = strtok(NULL, " "); //EncoderSpeed
	}
	tok = strtok(NULL, " "); //NumberChannels16Bit
	int NumberChannels16Bit;
	std::sscanf(tok, "%d", &NumberChannels16Bit);
	for (int i = 0; i < NumberChannels16Bit; i++)
	{
		int type = -1; // 0 DIST1 1 DIST2 2 DIST3 3 DIST4 4 DIST5 5 RSSI1 6 RSSI2 7 RSSI3 8 RSSI4 9 RSSI5
		char content[6];
		tok = strtok(NULL, " "); //MeasuredDataContent
		std::sscanf(tok, "%s", content);
		if (!strcmp(content, "DIST1"))	type = 0;
		else if (!strcmp(content, "DIST2"))	type = 1;
		else if (!strcmp(content, "DIST3"))	type = 2;
		else if (!strcmp(content, "DIST4"))	type = 3;
		else if (!strcmp(content, "DIST5"))	type = 4;
		else if (!strcmp(content, "RSSI1")) type = 5;
		else if (!strcmp(content, "RSSI2"))	type = 6;
		else if (!strcmp(content, "RSSI3"))	type = 7;
		else if (!strcmp(content, "RSSI4"))	type = 8;
		else if (!strcmp(content, "RSSI5"))	type = 9;
		else return RETURN_FAILED;
		tok = strtok(NULL, " "); //ScalingFactor
		int scalefactor;
		int	scalefactorinput;
		std::sscanf(tok, "%X", &scalefactorinput);
		if (scalefactorinput == 0x40000000)
			scalefactor = 2;
		else if (scalefactorinput == 0x40800000)
			scalefactor = 4;
		else
			scalefactor = 1;
		tok = strtok(NULL, " "); //ScalingOffset
		tok = strtok(NULL, " "); //Starting angle
		tok = strtok(NULL, " "); //Angular step width
		tok = strtok(NULL, " "); //NumberData
		int NumberData;
		std::sscanf(tok, "%X", &NumberData);
		scanCount = NumberData;
		if(NumberData != m_bufferA.nData_len)
			return RETURN_FAILED;
		LaserScanData* curBuffer = m_bBufferSwitch ? &m_bufferB : &m_bufferA;
		if (!m_bUpsideDown)
		{
			for (int i = 0; i < NumberData; i++)
			{
				int dat;
				tok = strtok(NULL, " "); //data
				std::sscanf(tok, "%X", &dat);
				dat = dat * scalefactor;
				if(type < 5)
					curBuffer->dist[i] = dat;
				else
					curBuffer->rssi[i] = dat;
			}
		}
		else
		{
			for (int i = NumberData - 1; i >= 0; i--)
			{
				int dat;
				tok = strtok(NULL, " "); //data
				std::sscanf(tok, "%X", &dat);
				dat = dat * scalefactor;
				if (type < 5)
					curBuffer->dist[i] = dat;
				else
					curBuffer->rssi[i] = dat;
			}
		}
	}
	tok = strtok(NULL, " "); //NumberChannels8Bit
	int NumberChannels8Bit;
	std::sscanf(tok, "%d", &NumberChannels8Bit);
	for (int i = 0; i < NumberChannels8Bit; i++)
	{
		int type = -1;
		char content[6];
		tok = strtok(NULL, " "); //MeasuredDataContent
		std::sscanf(tok, "%s", content);
		if (!strcmp(content, "DIST1"))	type = 0;
		else if (!strcmp(content, "DIST2"))	type = 1;
		else if (!strcmp(content, "DIST3"))	type = 2;
		else if (!strcmp(content, "DIST4"))	type = 3;
		else if (!strcmp(content, "DIST5"))	type = 4;
		else if (!strcmp(content, "RSSI1")) type = 5;
		else if (!strcmp(content, "RSSI2"))	type = 6;
		else if (!strcmp(content, "RSSI3"))	type = 7;
		else if (!strcmp(content, "RSSI4"))	type = 8;
		else if (!strcmp(content, "RSSI5"))	type = 9;
		else return RETURN_FAILED;
		tok = strtok(NULL, " "); //ScalingFactor
		int scalefactor;
		int	scalefactorinput;
		std::sscanf(tok, "%X", &scalefactorinput);
		if (scalefactorinput == 0x40000000)
			scalefactor = 2;
		else
			scalefactor = 1;

		tok = strtok(NULL, " "); //ScalingOffset
		tok = strtok(NULL, " "); //Starting angle
		tok = strtok(NULL, " "); //Angular step width
		tok = strtok(NULL, " "); //NumberData
		int NumberData;
		std::sscanf(tok, "%X", &NumberData);
		LaserScanData* curBuffer = m_bBufferSwitch ? &m_bufferB : &m_bufferA;
		if (!m_bUpsideDown) {
			for (int i = 0; i < NumberData; i++)
			{
				int dat;
				tok = strtok(NULL, " "); //data
				std::sscanf(tok, "%X", &dat);
				dat = dat * scalefactor;

				if (type < 5)
					curBuffer->dist[i] = dat;
				else
					curBuffer->rssi[i] = dat;
			}
		}
		else
		{
			for (int i = NumberData - 1; i >= 0; i--)
			{
				int dat;
				tok = strtok(NULL, " "); //data
				std::sscanf(tok, "%X", &dat);
				dat = dat * scalefactor;
				if (type < 5)
					curBuffer->dist[i] = dat;
				else
					curBuffer->rssi[i] = dat;
			}
		}
	}
	// cut Offset

	
	return RETURN_NON_ERROR;
}

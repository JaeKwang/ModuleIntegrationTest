#include "stdafx.h"

#include "IOHub.h"
#include "sensor\ComizoaIO.h"

using namespace sensor;
using namespace std;
using namespace IO_List;
using namespace eventManager;

CIOHub::CIOHub(string filename) {

	m_strIniFileName = filename;

	// 파일을 보고 각 장비에 맞게 IO 맵을 세팅
	Initialize();
}
CIOHub::~CIOHub()
{
	delete m_ComizoaIO;
}
int CIOHub::Initialize() {
	m_pINIReaderWriter = new PINIReadWriter(m_strIniFileName);	//설정파일 읽기

																//파일을 읽지 못한 경우 프로그램을 종료
	if (m_pINIReaderWriter->ParseError() < 0)
	{
		g_eventManager->PushTask(MSG_ERROR, "IOHub", ERROR_FILE_READ_FAILED, true, false);
		return RETURN_FAILED;
	}

	// Comizoa Config
	m_lNodeID = m_pINIReaderWriter->getIntValue("COMIZOA_CONFIG", "NODE_ID", 0);
	m_nDIOModuleSize = m_pINIReaderWriter->getIntValue("COMIZOA_CONFIG", "DIO_MODULE_COUNT", 0);
	m_DIOModule = new DIOModule[m_nDIOModuleSize];
	for (int i = 0; i < m_nDIOModuleSize; i++) {
		m_DIOModule[i].nDIStart = m_pINIReaderWriter->getIntValue("COMIZOA_CONFIG", "DIO" + to_string(i+1) + "_DI_START_CH_NUM", 0);
		m_DIOModule[i].nDINumber = m_pINIReaderWriter->getIntValue("COMIZOA_CONFIG", "DIO" + to_string(i + 1) + "_DI_CH_NUM", 0);
		m_DIOModule[i].nDOStart = m_pINIReaderWriter->getIntValue("COMIZOA_CONFIG", "DIO" + to_string(i + 1) + "_DO_START_CH_NUM", 0);
		m_DIOModule[i].nDONumber = m_pINIReaderWriter->getIntValue("COMIZOA_CONFIG", "DIO" + to_string(i + 1) + "_DO_CH_NUM", 0);
		m_DIOModule[i].nPinNum = m_DIOModule[i].nDINumber + m_DIOModule[i].nDONumber;
	}
	m_ComizoaIO = new CComizoaIO("ComizoaIO", m_lNodeID, m_DIOModule, m_nDIOModuleSize);

	// DI & DO Update
	m_DIPinType = new IOPinType[PIN_SIZE];
	m_DOPinType = new IOPinType[POUT_SIZE];
	for (int i = 0; i < m_nDIOModuleSize; i++) {
		for (int j = 0; j < m_DIOModule[i].nDINumber; j++) {
			int nIOCode = m_pINIReaderWriter->getIntValue("DIO" + to_string(i + 1) + "_DIN_" + to_string(j), "IOCODE", -1);
			if (nIOCode != -1) {
				m_DIPinType[nIOCode].strPinName = m_pINIReaderWriter->getStringValue("DIO" + to_string(i + 1) + "_DIN_" + to_string(j), "NAME", "");
				m_DIPinType[nIOCode].strModel = m_pINIReaderWriter->getStringValue("DIO" + to_string(i + 1) + "_DIN_" + to_string(j), "MODEL", "");
				m_DIPinType[nIOCode].nDIONumber = i;
				m_DIPinType[nIOCode].nPinBase = 0;
				m_DIPinType[nIOCode].nPinPosition = j;
				m_DIPinType[nIOCode].bActive = m_pINIReaderWriter->GetBoolean("DIO" + to_string(i + 1) + "_DIN_" + to_string(j), "ACTIVE", false);
			}
		}
		for (int j = 0; j < m_DIOModule[i].nDONumber; j++) {
			int nIOCode = m_pINIReaderWriter->getIntValue("DIO" + to_string(i + 1) + "_DOUT_" + to_string(j), "IOCODE", -1);
			if (nIOCode != -1) {
				m_DOPinType[nIOCode].strPinName = m_pINIReaderWriter->getStringValue("DIO" + to_string(i + 1) + "_DOUT_" + to_string(j), "NAME", "");
				m_DOPinType[nIOCode].strModel = m_pINIReaderWriter->getStringValue("DIO" + to_string(i + 1) + "_DOUT_" + to_string(j), "MODEL", "");
				m_DOPinType[nIOCode].nDIONumber = i;
				m_DOPinType[nIOCode].nPinBase = m_DIOModule[i].nDINumber;
				m_DOPinType[nIOCode].nPinPosition = j;
				m_DOPinType[nIOCode].bActive = m_pINIReaderWriter->GetBoolean("DIO" + to_string(i + 1) + "_DOUT_" + to_string(j), "ACTIVE", true);
			}
		}
	}
	return RETURN_NON_ERROR;
}
int CIOHub::bitSet(int dioNum, int base, int offset, bool value) {
	
	CComizoaIO * c = dynamic_cast<CComizoaIO *>(m_ComizoaIO);
	int pinNum = base + offset;
	if (m_DIOModule[dioNum].nDINumber <= pinNum && m_DIOModule[dioNum].nDINumber + m_DIOModule[dioNum].nDONumber > pinNum)
		return c->bitSet(dioNum, base + offset, value);
	else
		return RETURN_FAILED;
}
int CIOHub::bitSet(eDO_Code IOPin, bool value) {
	const char * model = m_DOPinType[IOPin].strModel.c_str();
	if (_strcmpi(model, "comizoa")) {
		CComizoaIO * c = dynamic_cast<CComizoaIO *>(m_ComizoaIO);
		if (m_DOPinType[IOPin].bActive)
			return c->bitSet(m_DOPinType[IOPin].nDIONumber, m_DOPinType[IOPin].nPinPosition, value);
		else
			return c->bitSet(m_DOPinType[IOPin].nDIONumber, m_DOPinType[IOPin].nPinPosition, !value);
	}
	else {
		g_eventManager->PushTask(MSG_ERROR, "IOHub", ERROR_NOT_DEFINED_PIN, true, true);
		return RETURN_DATA_CHECK_FAILED;
	}
	return RETURN_NON_ERROR;
}
bool CIOHub::bitRead(int dioNum, int base, int offset, int * nErrorCode){
	CComizoaIO * c = dynamic_cast<CComizoaIO *>(m_ComizoaIO);
	return c->bitRead(dioNum, base+offset, nErrorCode);
}
bool CIOHub::bitRead(eDI_Code IOPin, int * nErrorCode) {
	if (m_DIPinType[IOPin].nPinPosition < 0) {
		*nErrorCode = RETURN_FAILED;
		return false;
	}
	CComizoaIO * c = dynamic_cast<CComizoaIO *>(m_ComizoaIO);
	int errorCode;
	bool ret = c->bitRead(m_DIPinType[IOPin].nDIONumber, m_DIPinType[IOPin].nPinPosition, &errorCode);
	*nErrorCode = errorCode;
	return ret;
}
bool CIOHub::bitRead(IO_List::eDO_Code IOPin, int * nErrorCode) {
	if (IOPin == 3)
		*nErrorCode = RETURN_NON_ERROR;
	if (m_DOPinType[IOPin].nPinPosition < 0) {
		*nErrorCode = RETURN_FAILED;
		return false;
	}
	CComizoaIO * c = dynamic_cast<CComizoaIO *>(m_ComizoaIO);
	int errorCode;
	bool ret= c->bitRead(m_DOPinType[IOPin].nDIONumber, m_DOPinType[IOPin].nPinBase+m_DOPinType[IOPin].nPinPosition, &errorCode);
	*nErrorCode = errorCode;
	return ret;
}
int CIOHub::getStatus() {
	return m_ComizoaIO->getStatus();
}
DIOModule* CIOHub::getDIOModule() {
	return m_DIOModule;
}
int CIOHub::getDIOModuleNumber() {
	return m_nDIOModuleSize;
}
IOPinType* CIOHub::getDIModule() {
	return m_DIPinType;
}
IOPinType* CIOHub::getDOModule() {
	return m_DOPinType;
}
int CIOHub::findPin(int dioNum, int offset, IOPinType * ret) {
	for (int i = 0; i < PIN_SIZE; i++) {
		if (m_DIPinType[i].nDIONumber == dioNum) {
			if (m_DIPinType[i].nPinPosition == offset) {
				ret->bActive = m_DIPinType[i].bActive;
				ret->nDIONumber = m_DIPinType[i].nDIONumber;
				ret->nPinBase = m_DIPinType[i].nPinBase;
				ret->nPinPosition = m_DIPinType[i].nPinPosition;
				ret->strModel = m_DIPinType[i].strModel;
				ret->strPinName = m_DIPinType[i].strPinName;
				return RETURN_NON_ERROR;
			}
		}
	}
	for (int i = 0; i < POUT_SIZE; i++) {
		if (m_DOPinType[i].nDIONumber == dioNum) {
			if (m_DOPinType[i].nPinPosition == offset-m_DIOModule[dioNum].nDINumber) {
				ret->bActive = m_DOPinType[i].bActive;
				ret->nDIONumber = m_DOPinType[i].nDIONumber;
				ret->nPinBase = m_DOPinType[i].nPinBase;
				ret->nPinPosition = m_DOPinType[i].nPinPosition;
				ret->strModel = m_DOPinType[i].strModel;
				ret->strPinName = m_DOPinType[i].strPinName;
				return RETURN_NON_ERROR;
			}
		}
	}
	return RETURN_FAILED;
}

int CIOHub::setComizoaID(long id) {
	return ((CComizoaIO *)m_ComizoaIO)->setNodeID(id);
}
long CIOHub::getComizoaID() {
	return ((CComizoaIO *)m_ComizoaIO)->getNodeID();
}
void CIOHub::OccurError() {
	m_ComizoaIO->OccurError();
}
void CIOHub::Connect() {
	m_ComizoaIO->Connect();
}
void CIOHub::Reset() {
	m_ComizoaIO->Reset();
}
void CIOHub::Disconnect() {
	m_ComizoaIO->Disconnect();
}
#include "stdafx.h"//"../../stdafx.h"
#include "comm\SerialComm.h"

CSerialComm::CSerialComm()
{
	hComm=NULL;				// Initialization the Handle for Comport
	bFlowCtrl=FC_XONXOFF;	// Setup the flow_control
	fConnected=FALSE;		// thread stop
	bNotAvail=FALSE;
	local_buf_wr_idx=0;//pseudo
	local_buf_rd_idx=0;//pseudo
	m_bStartFlag = FALSE;

}

CSerialComm::~CSerialComm()
{
	DestroyComm();
}

int CSerialComm::GetBlock(unsigned char* data)
{
	int iLength = 0;
	if(local_buf_rd_idx == local_buf_wr_idx) 
	{
		data[0]=0x00;
		return 0; 
	}
	for(iLength =0; local_buf_rd_idx!=local_buf_wr_idx; iLength++)
	{	
		data[iLength]=local_buff[local_buf_rd_idx++];
		//printf("getdata data = %x\n",data[len]);
		if(local_buf_rd_idx == MAXBLOCK) local_buf_rd_idx=0;
	}	 
	return iLength;	
}


void CSerialComm::PutData(unsigned char data)
{
	local_buff[local_buf_wr_idx++]=data;
	if(local_buf_wr_idx == MAXBLOCK) local_buf_wr_idx=0;
	if(local_buf_wr_idx == local_buf_rd_idx) local_buf_rd_idx++;		//buff overflow
	if(local_buf_rd_idx == MAXBLOCK) local_buf_rd_idx=0;
}

char CSerialComm::GetData(void)
{
	bNotAvail=FALSE;
	if(local_buf_rd_idx == local_buf_wr_idx) 
	{
		bNotAvail=TRUE;
		return 0; 
	}

	unsigned char data=local_buff[local_buf_rd_idx++];
	
	if(local_buf_rd_idx == MAXBLOCK) local_buf_rd_idx=0;
	if(local_buf_rd_idx == local_buf_wr_idx) bNotAvail=TRUE;
	return data;	
}


// copy receive data to 'data'
void CSerialComm::SetReadData(unsigned char* data, int len)
{
	if(fConnected == TRUE){
		for( int i=0; i< len; i++){
			PutData(data[i]);
		}
	}
}


//set up hWnd which is to deliver message
void CSerialComm::SetHwnd(HWND hwnd)
{
	m_hWnd=hwnd;
}

// set up comport
void CSerialComm::SetComport(int port, DWORD rate, BYTE byteSize, BYTE stop, BYTE parity)
{
	bPort=port;
	dwBaudRate=rate;
	bByteSize=byteSize;
	bStopBits=stop;
	bParity=parity;
}

void CSerialComm::SetXonOff(BOOL chk)
{
	fXonXoff=chk;
}

void CSerialComm::SetDtrRts(BYTE chk)
{
	bFlowCtrl=chk;
}

// create comport information
// set up after doing SetComport()->SetXonOff()->SetDtrRts()
BOOL CSerialComm::CreateCommInfo()
{
	osWrite.Offset=0;
	osWrite.OffsetHigh=0;
	osRead.Offset=0;
	osRead.OffsetHigh=0;

	// creat EVENT. manual reset event, initial no-signal condition
	osRead.hEvent=CreateEvent(NULL, TRUE, FALSE, NULL);
	if(osRead.hEvent=NULL) {

		return FALSE;
	}
	osWrite.hEvent=CreateEvent(NULL, TRUE, FALSE, NULL);
	if(osWrite.hEvent=NULL) {
		CloseHandle(osRead.hEvent);

		return FALSE;
	}

	return TRUE;
}

// attemp to connect after opening comport
BOOL CSerialComm::OpenComport()
{
	char szPort[20];
	BOOL fRetVal;
	COMMTIMEOUTS CommTimeOuts;
	if(bPort > 20)
		lstrcpy((LPWSTR)szPort, _T("error"));
	else 
		wsprintf((LPWSTR)szPort, _T("\\\\.\\COM%d"), bPort);

	if((hComm = CreateFile((LPCWSTR)szPort, GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL)) == (HANDLE)-1)
		return FALSE;
	else {
		// Set data exchange method in comport to char unit to a default
		SetCommMask(hComm, EV_RXCHAR);
		SetupComm(hComm, 4096, 4096);
		// clean completely in case device has wastes
		PurgeComm(hComm, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
		CommTimeOuts.ReadIntervalTimeout=0xFFFFFFFF;
		CommTimeOuts.ReadTotalTimeoutMultiplier=0;
		CommTimeOuts.ReadTotalTimeoutConstant=200;
		CommTimeOuts.WriteTotalTimeoutMultiplier=0;
		CommTimeOuts.WriteTotalTimeoutConstant=200;
		SetCommTimeouts(hComm, &CommTimeOuts);
	}

	fRetVal = SetupConnection();

	if (fRetVal)
	{
		fConnected = TRUE;
	}
	else
	{
		fConnected=FALSE;
		CloseHandle(hComm);
	}
	return fRetVal;
}

BOOL CSerialComm::SetupConnection()
{
	BOOL fRetVal;
	//BYTE bSet;
	DCB dcb;
	dcb.DCBlength=sizeof(DCB);
	GetCommState(hComm, &dcb);		// receive dcb's default value.

	dcb.BaudRate=dwBaudRate;
	dcb.ByteSize=bByteSize;
	dcb.Parity=bParity;
	dcb.StopBits=bStopBits;
	
	fRetVal=SetCommState(hComm, &dcb);

	return fRetVal;
}

// read data from comprot
int CSerialComm::ReadCommBlock(LPSTR lpszBlock, int nMaxLength)
{
	BOOL fReadStat;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	DWORD dwLength;

	//only try to read number of bytes in queue

	ClearCommError(hComm, &dwErrorFlags, &ComStat);
	dwLength = min((DWORD)nMaxLength, ComStat.cbInQue);
	if (dwLength > 0) {
		fReadStat = ReadFile(hComm, lpszBlock, dwLength, &dwLength, &osRead);
		if (!fReadStat) {
		}
	}
	return dwLength;
}


// remove comport completely
BOOL CSerialComm::DestroyComm()
{
	if(fConnected) CloseConnection();
	return TRUE;
}

// close connection
BOOL CSerialComm::CloseConnection()
{
	fConnected = false;
	if (hComm != INVALID_HANDLE_VALUE) {
		CloseHandle(hComm);
		hComm = INVALID_HANDLE_VALUE;
		return true;
	}
	return false;
}

BOOL CSerialComm::WriteCommBlock(LPSTR lpByte, DWORD dwBytesToWrite)
{
	BOOL fWriteStat;
	DWORD dwBytesWritten;
	fWriteStat=WriteFile(hComm, lpByte, dwBytesToWrite, &dwBytesWritten, &osWrite);
	if(!fWriteStat) {
		//Error Message
	}

	return TRUE;
}

bool CSerialComm::clearport()
{
	PurgeComm(hComm, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	bNotAvail = FALSE;
	local_buf_wr_idx = 0;//pseudo
	local_buf_rd_idx = 0;//pseudo
	return true;
}
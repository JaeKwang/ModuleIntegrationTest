//////////////////////////////////////////////////////
// Communication files for Robot applications
// 
// Copyright (c) 2002-2011. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://dart.kitech.re.kr
// Written by KwangWoong Yang<page365@gmail.com>
//

#include "stdafx.h"//"../../stdafx.h"
#include <assert.h>
#include "SockTcp.h"
//#include "DebugLog.h"
#define DESIRED_WINSOCK_VERSION 0x0202
#define MINIMUM_WINSOCK_VERSION 0x0001
#pragma comment (lib,"ws2_32.lib")

using namespace std;

// SD_BOTH is defined in <winsock2.h> file
#define SD_BOTH         0x02

CSockTcp::CSockTcp()
{
	_hSocket = INVALID_SOCKET;
	WSADATA wsadata;
	if(!WSAStartup(DESIRED_WINSOCK_VERSION,&wsadata)){
		if(wsadata.wVersion<MINIMUM_WINSOCK_VERSION){
			WSACleanup();
		}
	}
}


CSockTcp::CSockTcp (const char *hostName, WORD portNo) :
_hSocket(INVALID_SOCKET),
_hostName(hostName),
_portNo(portNo)
{
	_hSocket = INVALID_SOCKET;
}

CSockTcp::~CSockTcp()
{
	if(_hSocket != INVALID_SOCKET)
	{
		Close();
	}
}

void CSockTcp::Init(const char *hostName, WORD portNo)
{
	_hSocket = INVALID_SOCKET;
	_hostName = hostName;
	_portNo = portNo;
}

bool CSockTcp::IsValidHandle()
{
	return _hSocket != INVALID_SOCKET;
}

bool CSockTcp::OpenServer()
{
	assert(_hSocket == INVALID_SOCKET);

	_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(_hSocket == INVALID_SOCKET)
	{
		return false;
	}

	// accept()에서 blocking 되는 것을 막기위해 non-blocking으로 설정한다.
	int ioctl_opt = 1;
	if(ioctlsocket(_hSocket, FIONBIO, (unsigned long *)&ioctl_opt) == SOCKET_ERROR)
	{
		closesocket(_hSocket);
		_hSocket = INVALID_SOCKET;
		return false;
	}

	// 소켓에서 사용하던 Port No를 재사용 가능하도록 한다.
	// listen하던 소켓을 닫은 후 새로 연 경우 한동안 bind ()가 안되는 현상을 막기위해 설정한다.
	bool opt_reuseaddr = true;
	if(setsockopt(_hSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt_reuseaddr, sizeof(opt_reuseaddr)) == SOCKET_ERROR)
	{
		PrintErrorMessage("ERROR: CSockTcp::OpenServer(): setsockopt(): ");
		closesocket(_hSocket);
		_hSocket = INVALID_SOCKET;
		return false;
	}

	// IP address와 port number를 소켓에 바인드 한다.
	memset((char *)&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr.sin_family      = AF_INET;
	_sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	_sockAddr.sin_port        = htons(_portNo);
	if(::bind(_hSocket, (struct sockaddr *) &_sockAddr, (int)sizeof(_sockAddr)) < 0)
	{
		PrintErrorMessage("ERROR: CSockTcp::OpenServer(): bind(): ");	
		closesocket(_hSocket);
		_hSocket = INVALID_SOCKET;
		return false;
	}

	listen(_hSocket, 1);	

	return true;
}

bool CSockTcp::OpenClient ()
{
	assert(_hSocket == INVALID_SOCKET);

	_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(_hSocket == INVALID_SOCKET)
	{
		PrintErrorMessage("ERROR: CSockTcp::OpenClient(): socket(): ");
		return false;
	}
	// Set the socket to blocking mode.
	int ioctl_opt = 0;
	if(ioctlsocket(_hSocket,FIONBIO,(unsigned long *)&ioctl_opt) == SOCKET_ERROR)
	{
		PrintErrorMessage("ERROR: CSockTcp::OpenClient(): ioctlsocket(): ");
		closesocket(_hSocket);
		_hSocket = INVALID_SOCKET;
		return false;
	}

	memset((char *)&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_port = htons(_portNo);
	unsigned long haddr = inet_addr(_hostName.c_str());
	if(haddr == INADDR_NONE)
	{
		struct hostent *hsock = gethostbyname(_hostName.c_str());
		if(hsock != NULL)
		{
			_sockAddr.sin_addr.s_addr  = *(unsigned long *)hsock->h_addr_list[0];
		}
		else
		{
			PrintErrorMessage("ERROR: CSockTcp::OpenClient(): gethostbyname(): ");
			closesocket(_hSocket);
			_hSocket = INVALID_SOCKET;
			return false;
		}
	}
	else
	{
		_sockAddr.sin_addr.s_addr = haddr;
	}

	return true;
}

void CSockTcp::Close()
{
	if(_hSocket != INVALID_SOCKET)
	{
		closesocket(_hSocket);
		_hSocket = INVALID_SOCKET;
	//	DebugLog ("INFO: socket closed");
	}
}

bool CSockTcp::Accept(bool *accept)
{
	assert(_hSocket != INVALID_SOCKET);

	int clilen = sizeof(_sockAddr);
	SOCKET hnewsock = ::accept(_hSocket, (struct sockaddr *) &_sockAddr, &clilen);		
	if(hnewsock == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		if(error == WSAETIMEDOUT || error == WSAEWOULDBLOCK)
		{
			// non-blocking 모드에서 timeout 되었을 때
			*accept = false;
			return true;
		}
		else
		{
			PrintErrorMessage("ERROR: CSockTcp::Accept(): accept(): ");
			closesocket(_hSocket);
			_hSocket = INVALID_SOCKET;
			return false;
		}
	}
	else
	{			
		// 현재 소켓 핸들을 닫고 새로운 소켓 핸들을 설정한다.
		closesocket(_hSocket);
		_hSocket = hnewsock;

		// client가 연결된 후에는 소켓을 blocking mode로 변경한다.
		int ioctl_opt = 0;
		if(ioctlsocket(_hSocket, FIONBIO, (unsigned long *)&ioctl_opt) == SOCKET_ERROR)
		{
			PrintErrorMessage("ERROR: CSockTcp::Accept(): ioctlsocket(): ");
			closesocket(_hSocket);
			_hSocket = INVALID_SOCKET;
			return false;
		}
	}
	*accept = true;
	return true;
}

bool CSockTcp::Connect(int nTimeout)
{
	// put socked in non-blocking mode
	u_long block = 1;
	if (ioctlsocket(_hSocket, FIONBIO, &block) == SOCKET_ERROR)
	{
		closesocket(_hSocket);
		return false;
	}
	if (connect(_hSocket, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			// connection failed
			closesocket(_hSocket);
			return false;
		}

		// connection pending

		fd_set setW, setE;

		FD_ZERO(&setW);
		FD_SET(_hSocket, &setW);
		FD_ZERO(&setE);
		FD_SET(_hSocket, &setE);

		timeval time_out = { 0 };
		time_out.tv_sec = long(nTimeout/1000.);
		time_out.tv_usec = (nTimeout%1000) * 1000;

		int ret = select(0, NULL, &setW, &setE, &time_out);
		if (ret <= 0)
		{
			// select() failed or connection timed out
			closesocket(_hSocket);
			if (ret == 0) {
				WSASetLastError(WSAETIMEDOUT);
			}
			return false;
		}

		if (FD_ISSET(_hSocket, &setE))
		{
			// connection failed
			closesocket(_hSocket);
			return false;
		}
	}

	// put socked in blocking mode...
	block = 0;
	if (ioctlsocket(_hSocket, FIONBIO, &block) == SOCKET_ERROR)
	{
		closesocket(_hSocket);
		return false;
	}
	return true;
}

int CSockTcp::Send(const BYTE *data, int len)
{
	assert(_hSocket != INVALID_SOCKET);

	if(len <= 0)
		return 0;

	int ret = ::send(_hSocket, (char *)data, len, 0);
	if(ret == 0)
	{
		return -1;
	}
	else if(ret == SOCKET_ERROR)
	{	// Socket error
		// PrintErrorMessage ("WARN: CSockTcp::Send(): send(): ");

		int error = WSAGetLastError();
		if(error == WSAETIMEDOUT || error == WSAEWOULDBLOCK)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else if(ret != len)
	{
	//	DebugLog ("ERROR: CSockTcp::Send(): send(): Can't send all data at one time.");
		return ret;
	}
	else
	{
		return ret;
	}
}

int CSockTcp::Recv (BYTE *data, int len)
{
	assert (_hSocket != INVALID_SOCKET);

	int ret = ::recv (_hSocket, (char *)data, len, 0);
	if(ret == 0) {
		// connection has been gracefully closed
		return -1;
	}
	else if(ret == SOCKET_ERROR) {	// Socket error
		// PrintErrorMessage ("WARN: CSockTcp::Recv(): recv(): ");

		int error = WSAGetLastError ();
		if(error == WSAETIMEDOUT || error == WSAEWOULDBLOCK) {
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		return ret;
	}
}

void CSockTcp::SetTimeout (int timeout)
{
	assert (_hSocket != INVALID_SOCKET);

	int opt_timeout = timeout;
	// socket의 opetion (receiving timeout 값) 설정
	if(setsockopt (_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt_timeout, sizeof(opt_timeout)) == SOCKET_ERROR) {
		PrintErrorMessage ("WARN: SetTimeout(): setsockopt(): ");
	}
	// socket의 opetion (sending timeout 값) 설정
	if(setsockopt (_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&opt_timeout, sizeof(opt_timeout)) == SOCKET_ERROR) {
		PrintErrorMessage ("WARN: SetTimeout(): setsockopt(): ");
	}
}

void CSockTcp::PrintErrorMessage (const char *pre)
{
	int errCode = WSAGetLastError();

	LPSTR errString = NULL;  // will be allocated and filled by FormatMessage
//	FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM, 0, errCode, 0, (LPSTR)&errString, 0, 0);
	
	//DebugLog("%s %d: %s", pre, errCode, errString);
	
	LocalFree (errString);
}
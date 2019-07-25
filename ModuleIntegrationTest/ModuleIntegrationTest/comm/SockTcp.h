//////////////////////////////////////////////////////
// Communication files for Robot applications
// 
// Copyright (c) 2002-2011. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://dart.kitech.re.kr
// Written by KwangWoong Yang<page365@gmail.com>
//


#pragma once
#include <winsock2.h>
#include <string>

using namespace std;

class CSockTcp
{
public:
	CSockTcp (const char *hostName, WORD portNo);
	virtual ~CSockTcp ();

	bool IsValidHandle ();
	int Send (const BYTE *data, int len);
	int Recv (BYTE *data, int len);

	bool OpenServer (); 
	bool OpenClient (); 
	void Close (); 
	bool Listen (); 
	bool Accept (bool *accept);
	bool Bind ();
	bool Connect (int nTimeout); 
	void SetTimeout (int timeout);
	

	CSockTcp();
	void Init(const char *hostName, WORD portNo);
public:
	string _hostName;
	short _portNo;

	SOCKET _hSocket;
	struct sockaddr_in _sockAddr;	

	void PrintErrorMessage (const char *pre);
};

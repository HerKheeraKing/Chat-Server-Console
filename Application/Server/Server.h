#pragma once
#include <WinSock2.h>
#include "stdint.h"

#define _CRT_SECURE_NO_WARNINGS 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

class Server
{
	public:

	int init(uint16_t port);
	int readMessage(char* buffer, int32_t size);
	int sendMessage(char* data, int32_t length);
	int alanticChase(char* data, int32_t length); 
	void stop();

	SOCKET listenSocket;
	SOCKET socketCom; 

};
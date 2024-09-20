#pragma once
//#include "Error.h" 
#include <winsock2.h>
#include "stdint.h"

//#define _CRT_SECURE_NO_WARNINGS 
//#define _WINSOCK_DEPRECATED_NO_WARNINGS

// Error Defining 
enum ErrorCodes : int 
{
	SUCCESS = 0, SHUTDOWN = 1, DISCONNECT = 2,
	BIND_ERROR = 3, CONNECT_ERROR = 4, SETUP_ERROR = 5,
	STARTUP_ERROR = 6, ADDRESS_ERROR = 7, PARAMETER_ERROR = 8
};

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


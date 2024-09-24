#pragma once
#include "Error.h"  
#include <winsock2.h>
#include "stdint.h"
#include <string>
using namespace std;

//#define _CRT_SECURE_NO_WARNINGS 
//#define _WINSOCK_DEPRECATED_NO_WARNINGS


class Server
{
public:

	// Variables
	struct timeval 
	{
		int tv_sec = 5;
		int tv_msec = 0;
	};

	uint8_t chatCapacity = 0;
	uint16_t tcpPort = 0; 
	uint16_t serverPort = 0; 
	char hostName[256];
	std::string fullHostName = "";

	// Functions 
	int init(uint16_t port);
	int readMessage(char* buffer, int32_t size);
	int sendMessage(char* data, int32_t length);
	int alanticChase(char* data, int32_t length);
	void stop();

	// Sockets 
	SOCKET listenSocket;
	SOCKET socketCom;

	// Socket manager & ready set for usage of sockets from socket manager
	fd_set masterSet;
	fd_set readySet; 

};


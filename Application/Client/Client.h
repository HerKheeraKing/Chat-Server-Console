#pragma once
#include "../platform.h"
#include "../definitions.h"

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

class Client
{
	public:

	int init(uint16_t port, char* address);
	int readMessage(char* buffer, int32_t size);
	int sendMessage(char* data, int32_t length);
	int alanticChase(char* data, int32_t length); 
	void stop();

	// Create socket 
	SOCKET clientSocket;
};
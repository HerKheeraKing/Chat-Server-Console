#pragma once
#include "Error.h"  
#include <winsock2.h>
#include <WS2tcpip.h> 
#include "stdint.h"
#include <string>
#include <vector>
#include <sstream>
#include "Command.h" 
#include "Functions.h"      
using namespace std;



#define _CRT_SECURE_NO_WARNINGS 
#define _WINSOCK_DEPRECATED_NO_WARNINGS



class Server 
{

public:

	// Variables
	int chatCapacity = 0; 
	int tcpPort = 0;  
	int serverPort = 0; 
	int numReady = 0; 
	char hostName[256] = "";
	int users = 0;    
	
	// Functions 
	int init(uint16_t port);
	int readMessage(SOCKET clientSocket, char* buffer, int32_t size);  
	int sendMessage(SOCKET clientSocket, const char* data, int32_t length); 
	int alanticChase(SOCKET clientSocket, const char* data, int32_t length); 
	void stop(); 
	 
	// Sockets 
	SOCKET listenSocket;
	SOCKET newClientSocket; 
	SOCKET clientSocket;    

	// Socket manager & ready set for usage of sockets from socket manager
	fd_set masterSet;
	fd_set readySet;
	   

};



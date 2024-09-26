#include "Server.h"
#include <iostream> 
using namespace std; 

int Server::init(uint16_t port)
{
	// Create socket
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		return SETUP_ERROR;
	}
	
	// Bind Socket to port
	sockaddr_in sAdress;
	sAdress.sin_family = AF_INET;
	sAdress.sin_addr.S_un.S_addr = INADDR_ANY;
	sAdress.sin_port = htons(port);

	int result = bind(listenSocket, (SOCKADDR*)&sAdress, sizeof(sAdress));
	if (result == SOCKET_ERROR)
	{
		return BIND_ERROR;
	}

	// Getting host name 
	if (gethostname(hostName, sizeof(hostName)) == 0) 
	{
		std::string fullHostName(hostName); 
		std::cout << "\n";
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Host Name: " << fullHostName << std::endl;  
	}
	else
	{
		return HOSTNAME_ERROR;  
	}

	// TODO: collect host IP & display to console


	// Listening queue for connections 
	result = listen(listenSocket, 1);
	if (result == SOCKET_ERROR)
	{
		return SETUP_ERROR;
	}

	socketCom = accept(listenSocket, NULL, NULL);
	if (socketCom == INVALID_SOCKET)
	{
		// Check for error & already shutdown 
		if (WSAGetLastError() == WSAESHUTDOWN)
		{
			return SHUTDOWN;
		}
		else
		{
			return CONNECT_ERROR;
		}
	}

	// Master Set set-up
	// Timeout in header
	FD_ZERO(&masterSet); 
	FD_SET(socketCom, &masterSet); 
	FD_SET(listenSocket, &masterSet);  

	struct timeval timeout { 5, 0 }; 
	timeout.tv_sec = 5; 
	timeout.tv_usec = 0;   

	//while (true) 
	{
	//	readySet = masterSet;
	//	numReady = select(0, &readySet, NULL, NULL, &timeout);

	//	// If listening socket is ready
	//	if (FD_ISSET(listenSocket, &readySet)) 
	//	{
	//		// Accept new connection 
	//	    socketCom = accept(listenSocket, NULL, NULL); 
	//		if (socketCom == INVALID_SOCKET) 
	//		{
	//			// Check for error & already shutdown 
	//			if (WSAGetLastError() == WSAESHUTDOWN) 
	//			{
	//				return SHUTDOWN; 
	//			}
	//			else
	//			{
	//				return CONNECT_ERROR; 
	//			}
	//	    }
	//		// Add to master set
	//		FD_SET(socketCom, &masterSet);  

	//	// Process each ready client 
	//	for (int i = 0; i < chatCapacity; i++)
	//	{
	//		if (FD_ISSET(clientSocket[i], &readySet))  
	//		{
	//			// Process client 
	//			 
	//			
	//		}
	//	}
	}


	return SUCCESS;
}


int Server::readMessage(char* buffer, int32_t size)
{
	int total = 0;

	// Get length of data
	uint8_t length = 0;
	int messLength = recv(socketCom, (char*)&length, 1, 0);


	if (messLength > size)
	{
		return PARAMETER_ERROR;
	}

	do
	{
		messLength = recv(socketCom, buffer + total, length - total, 0);

		if (messLength < 1)
		{
			if (messLength == -1)
			{
				return DISCONNECT;
			}

			return SHUTDOWN;
		}
		else
		{
			total += messLength;
		}

	} while (total < length);

	return SUCCESS;
}


int Server::alanticChase(char* data, int32_t length)
{
	int bytesSent = 0;
	int result;

	while (bytesSent < length)
	{
		result = send(socketCom, (const char*)data + bytesSent, length - bytesSent, 0);

		if (result < 1)
		{
			if (result == -1)
			{
				return DISCONNECT;
			}

			return SHUTDOWN;
		}

		bytesSent += result;
	}

	return bytesSent;
}


int Server::sendMessage(char* data, int32_t length)
{
	if (length < 0 || length > 255)
	{
		return PARAMETER_ERROR;
	}

	alanticChase((char*)&length, 1);
	alanticChase(data, length);

	return SUCCESS;
}

void Server::stop()
{
	shutdown(listenSocket, SD_BOTH); 
	shutdown(socketCom, SD_BOTH);
	closesocket(listenSocket);
	closesocket(socketCom);
}
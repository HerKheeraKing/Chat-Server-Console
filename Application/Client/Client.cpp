#include "Client.h"
#include <WS2tcpip.h>

int Client::init(uint16_t port, char* address)
{
	unsigned long add;
	inet_pton(AF_INET, address, &add);
	if (add == -1) 
	{
		return ADDRESS_ERROR;
	}

	// Create Socket 
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) 
	{
		return SETUP_ERROR;
	}

	// Connect 
	sockaddr_in serverAddr;
	serverAddr.sin_addr.S_un.S_addr = add;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_family = AF_INET;
	

	int result = connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR) 
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
		
		
	// Notes: https://www.tutorialspoint.com/validate-ip-address-in-cplusplus
	return SUCCESS;
}

int Client::readMessage(char* buffer, int32_t size)
{
	int total = 0;

	// Get length of data
	uint8_t length = 0;
	int messLength = recv(clientSocket, (char*)&length, 1, 0);

	if (messLength > size) 
	{
		return PARAMETER_ERROR; 
	}

	do
	{
		messLength = recv(clientSocket, buffer + total, length - total, 0);

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


int Client::alanticChase(char* data, int32_t length) 
{
	int bytesSent = 0;
	int result;

	while (bytesSent < length)
	{
		result = send(clientSocket, (const char*)data + bytesSent, length - bytesSent, 0);

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


int Client::sendMessage(char* data, int32_t length)
{
	if (length < 0 || length > 255)
	{
		return PARAMETER_ERROR;
	}
		
	alanticChase((char*)&length, 1);
	alanticChase(data, length);

	return SUCCESS;
}



void Client::stop()
{
	shutdown(clientSocket, SD_BOTH); 
	closesocket(clientSocket);
}
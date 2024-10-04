#include "Server.h"
#include <iostream> 
using namespace std; 

   
extern Functions func;  
extern Command commands; 

int Server::init(uint16_t port)
{
	// Create socket
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		return SETUP_ERROR;
	}
	
	//// Set up Non blocking
	u_long mode = 1;  
	if (ioctlsocket(listenSocket, FIONBIO, &mode) == SOCKET_ERROR)  
	{
		return SOCKET_ERROR;  
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

	// Collect host IP & display to console
	// Initialize results & hints 
	// Init hints struct to zero.
	// Accept both IP 4/6, look for TCP socket.
	// Return addr error if lookup fails.
	// Create buffer for addr 4&6
	// Handle IP4
	// Handle IP6
	// Continue if not either
	// Print IP adddr to console 
	addrinfo* res; 
	addrinfo hints; 
	memset(&hints, 0, sizeof(hints)); 

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(hostName, nullptr, &hints, &res) != 0)   
	{
		return ADDRESS_ERROR; 
	}

	char ip4[INET_ADDRSTRLEN] = "";
	char ip6[INET6_ADDRSTRLEN] = ""; 

	for (addrinfo* i = res; i != nullptr; i = i->ai_next)   
	{
		void* addr;

		if (i->ai_family == AF_INET) // IP4
		{
			sockaddr_in* ipv4 = (sockaddr_in*)i->ai_addr;
			addr = &ipv4->sin_addr;
			inet_ntop(i->ai_family, addr, ip4, sizeof(ip4));
		}
		else if (i->ai_family == AF_INET6) // IP6
		{
			sockaddr_in6* ipv6 = (sockaddr_in6*)i->ai_addr;
			addr = &ipv6->sin6_addr;
			inet_ntop(i->ai_family, addr, ip6, sizeof(ip6));
		}

		else continue; 
	}

	std::cout << "IPv4: " << ip4 << '\n' << "IPv6: " << ip6 << std::endl;
	std::cout << "-----------------------------------------" << std::endl; 
	std::cout << '\n'; 

	// Notes: https://cplusplus.com/forum/windows/280069/ 

	// Listening queue for connections 
	// Multiple connections 
	result = listen(listenSocket, SOMAXCONN);  
	if (result == SOCKET_ERROR)
	{
		return SETUP_ERROR;
	}


	// Master Set set-up
	// Timeout in header
	FD_ZERO(&masterSet); 
	FD_SET(listenSocket, &masterSet);   

	while (true)
	{
		struct timeval timeout { 3, 0 };
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;

		readySet = masterSet;
		numReady = select(0, &readySet, nullptr, nullptr, &timeout);

		if (numReady == SOCKET_ERROR)
		{
			return READY_ERROR;
		}
		 
		for (int i = 0; i < numReady; i++)
		{
			// Set ready socket[i] client socket 
			clientSocket = readySet.fd_array[i];  
			if (FD_ISSET(listenSocket, &readySet)) 
			{
				
				// Accept connection 
		        newClientSocket = accept(listenSocket, nullptr, nullptr);  
				//users++; 

				//// Checking for chat capacity 
				//if (users >= chatCapacity)   
				//{
				//	std::cout << "Chat at full capacity. Please try again later." << std::endl;      

				//	// At capacity message to GUI & server
				//	// Handle new user coming in
				//	const char* mess = "Chat is currently full. Please try again later. ";  
				//	size_t length = strlen(mess);  
				//	send(newClientSocket, (char*)mess, static_cast<int32_t>(length), 0);  
				//	closesocket(newClientSocket);  
				//	users--; 
				//	continue;  
				//}

				// Error checking new client socket 
				if (newClientSocket == INVALID_SOCKET) 
						{
							// Check for error & already shutdown
							if (WSAGetLastError() == WSAEWOULDBLOCK) 
							{
								continue;
							}
							else if (WSAGetLastError() == WSAESHUTDOWN) 
							{
								return SHUTDOWN; 
							}
							else
							{
								return CONNECT_ERROR; 
							}
						}

				// + new connection to master
				FD_SET(newClientSocket, &masterSet);  

				// Welcome message
			const char* welcomeMess = "Welcome to your server, use '@' for commands & '@help' for list of commands.\r\n ";   
			size_t length = strlen(welcomeMess); 
			sendMessage(newClientSocket, welcomeMess, static_cast<int32_t>(length));  
				
			}
			else 
			{
				// Buffer 
		    	char messageBuffer[4096] = ""; 
				ZeroMemory(messageBuffer, 4096); 

				// Accept new message 
				// Input 
				int input = readMessage(clientSocket, messageBuffer, 4096);     
				if (input < 0) 
				{
					// Disconnect 
					closesocket(clientSocket); 
					FD_CLR(clientSocket, &masterSet);  
					users--; 
				}
				else if (messageBuffer[0] != '\0')
				{ 
					// If user uses command 
					std::string userInput(messageBuffer); 

					std::string command = userInput.substr(1);    

					if (command == "@help" || command == "@clear" || command.substr(0, 9) == "@register" || command.substr(0, 6) == "@login" || command == "@logout")
					{
					  std::string sendMsgTxt = commands.setCommandCase(command); 
			           
					  if (!(sendMsgTxt.empty())) 
					  {
						  sendMessage(clientSocket, sendMsgTxt.c_str(), static_cast<int32_t>(sendMsgTxt.size() + 1));        
					  }
					  
					}
					else
					{ 
						// Send message to clients 
						for (int i = 0; i < masterSet.fd_count; i++)
						{
							// Sock to handle message sending 
							SOCKET sendSock = masterSet.fd_array[i]; 
							if (sendSock != listenSocket && sendSock != clientSocket) 
							{
								// Create object to build message 
								// Output user format
								// Convert from object to string
								ostringstream ss;  
								ss << "User " << commands.usersSignUp[commands.username] << ": " << messageBuffer << ""; 
								std::string strOut = ss.str(); 

								sendMessage(sendSock, strOut.c_str(), static_cast<int32_t>(strOut.size() + 1));   
							} 
						}
					}
				}
			}
		}
	}


   return SUCCESS; 
}

 
int Server::readMessage(SOCKET clientSocket, char* buffer, int32_t size)            
{
	int total = 0; 

	// Get length of data
	uint8_t length = 0; 
	int messLength = recv(clientSocket, (char*)&length, 1, 0);   

	if (messLength < 1 || length == 0)  
	{
		return SHUTDOWN; 
	}
	 
	if (length > size - 1) 
	{
		return PARAMETER_ERROR;  
	}

	// Add it
	buffer[total] = (char)length; 
	total++;  

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

	buffer[total] = '\0'; 

	return SUCCESS; 

	
}


int Server::alanticChase(SOCKET clientSocket, const char* data, int32_t length)  
{
	int bytesSent = 0;
	int result;

	while (bytesSent < length)
	{
		result = send(clientSocket, data + bytesSent, length - bytesSent, 0);  

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


int Server::sendMessage(SOCKET clientSocket, const char* data, int32_t length)  
{

	if (length < 0 || length > 255) 
	{
		return PARAMETER_ERROR;
	}

	alanticChase(clientSocket, (char*)&length, 1); 
	alanticChase(clientSocket, data, length); 

	return SUCCESS;
}

void Server::stop()
{
	shutdown(listenSocket, SD_BOTH);  
	shutdown(newClientSocket, SD_BOTH); 
	closesocket(listenSocket);
	closesocket(newClientSocket);
}


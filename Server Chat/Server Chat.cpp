#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include "Server.h"
#include "Error.h"
#include "WS2tcpip.h"
#include "Functions.h"
#include "Command.h" 

// Instances
Server server; 
Functions func;

int main()
{
    WSADATA wsaData; 
    WSAStartup(WINSOCK_VERSION, &wsaData); 

    // Prompt the user for TCP Port number, chat..
    // capacity, and the command character is set to '@'.
    std::cout << "Welcome to the Chat Server, please provide the following information to get started!\n\n" << std::endl;

    func.TCPport(); 
    std::cout << "\n\n"; 
    func.chatCapacity(); 

    // Bind with user port 
    server.init(server.tcpPort);        
    
    // Display host name & IP on the server console upon startup

     
    

   
   
}

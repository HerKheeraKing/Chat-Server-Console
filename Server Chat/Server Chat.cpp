#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include "Server.h"
#include "Error.h"
#include "WS2tcpip.h"
#include "Functions.h"

// Instances
Server server; 
Functions func;

int main()
{
    // Prompt the user for TCP Port number, chat..
    // capacity, and the command character is set to '@'.
    std::cout << "Welcome to the Chat Server, please provide the following information to get started!\n\n" << std::endl;

    func.TCPport(); 
    
    std::cout << "\n\n";

    func.chatCapacity(); 
    

    //  TODO: Display host name & IP on the server console upon startup
    //std::cout << "Host Name: " << server.fullHostName << std::endl; 
}

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include "Server.h"
#include "Error.h"
#include "WS2tcpip.h"


// Instances
Server server; 

int main()
{
    // Prompt the user for TCP Port number, chat..
    // capacity, and the command character is set to '@'.
    std::cout << "Welcome to the Chat Server, please provide the following information to get started!" << std::endl;

    std::cout << "TCP Port Number: " << std::endl; 
    std::cin >> server.tcpPort; 

    std::cout << "Chat Capacity: " << std::endl;
    std::cin >> server.chatCapacity;
}

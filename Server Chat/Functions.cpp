#include "Functions.h"
#include <iostream>

//TODO: Error checking  
// letters, chat capacity 
void Functions::TCPport()
{
    std::cout << "TCP Port Number: " << std::endl;
    std::cin >> server.tcpPort; 
    if (server.tcpPort < 0 || server.tcpPort > 65535 || std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "\nInvalid port number, please provide a port number in the range of '0 - 65, 535' " << std::endl;
        std::cout << "Port number: ";
        std::cin >> server.tcpPort;
    } 

    std::cout << "You entered a valid TCP port number! " << server.tcpPort << std::endl;
}

void Functions::chatCapacity()  
{
    std::cout << "Chat Capacity: " << std::endl; 
    std::cin >> server.chatCapacity; 
    if (server.chatCapacity < 0 || server.chatCapacity > 4 || std::cin.fail()) 
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');  
        std::cout << "\nInvalid chat capacity, please provide a usage betweem '1 - 4' " << std::endl;
        std::cout << "Chat Capacity: ";
        std::cin >> server.chatCapacity;
    }

    std::cout << "You entered a valid chat capacity! " << server.chatCapacity << std::endl;
}



#include "Functions.h"
#include <iostream>

 // Prompt user for port num & chat capacity
 // Storing input into string for parsing for invalid characters
 // while spaces & non digits, throw errors & re-prompt
 // try catch to handle exeptions outside of said errors
 // letters, special char, spaces , chat capacity  

// Instances
extern Server server; 

void Functions::TCPport()
{
    std::cout << "TCP Port Number: " << std::endl;

    std::string var;  

    while (true) 
    {
        getline(std::cin, var); 

        // Check for spaces 
        if (var.find(' ') != string::npos) 
        {
            std::cout << "\n"; 
            std::cout << "Invalid input, TCP port number cannot contain spaces." << std::endl; 
            continue; 
        }

        // Check for special characters / non digit 
        
        bool isValid = true; 
        for (char c : var) 
        {
            if (!std::isdigit(c))   
            {
                std::cout << "\n"; 
                std::cout << "Invalid input, TCP port number cannot contain letters or special characters." << std::endl;  
                isValid = false; 
                break;
            }
        }

        if (!isValid) 
        {
            continue;
        }

        // Special internal cases
        try 
        {
            server.tcpPort = std::stoi(var);
            if (server.tcpPort < 0 || server.tcpPort > 65535)
            {
                std::cout << "\n";
                std::cout << "\nInvalid port number, please provide a port number in the range of '0 - 65, 535' " << std::endl;
                continue;
            }

            // Clear console if correct 
            system("cls"); 
            std::cout << "\n";
            std::cout << "You entered a valid TCP port number! " << server.tcpPort << std::endl; 
            break; 
        }
        catch (const std::invalid_argument&) 
        {
            std::cout << "\n";
            std::cout << "Invalid, please enter a numeric port." << std::endl; 
        }
        catch (const std::out_of_range&) 
        {
            std::cout << "\n";
            std::cout << "Invalid, please enter a port in range '0 - 65, 535' ." << std::endl;  
        }
    }
}



void Functions::chatCapacity()  
{
    std::cout << "Chat Capacity: " << std::endl; 
    
    std::string var; 

    while (true) 
    {
        getline(std::cin, var); 

        // Check for spaces 
        if (var.find(' ') != string::npos) 
        {
            std::cout << "\n";
            std::cout << "Invalid input, chat capacity value cannot contain spaces." << std::endl; 
            continue;
        }

        // Check for special characters / non digit 

        bool isValid = true; 
        for (char c : var) 
        {
            if (!std::isdigit(c)) 
            {
                std::cout << "\n"; 
                std::cout << "Invalid input, chat capacity value cannot contain letters or special characters." << std::endl; 
                isValid = false; 
                break; 
            }
        }

        if (!isValid) 
        {
            continue; 
        }

        // Special internal cases 
        try
        {
            server.chatCapacity = std::stoi(var);  
            if (server.chatCapacity < 2 || server.chatCapacity > 4) 
            {
                std::cout << "\n"; 
                std::cout << "\nInvalid chat capacity, please provide a number in the range of '2 - 4' " << std::endl; 
                continue;
            }

            // Clear console if correct 
            system("cls"); 
            std::cout << "\n"; 
            std::cout << "You entered a valid capacity '" << server.chatCapacity << "', welcome!" << std::endl;     
            break;
        }
        catch (const std::invalid_argument&) 
        {
            std::cout << "\n"; 
            std::cout << "Invalid, please enter a numeric port." << std::endl; 
        }
        catch (const std::out_of_range&) 
        {
            std::cout << "\n"; 
            std::cout << "Invalid, please enter a port in range '2 - 4' ." << std::endl; 
        }
    }
}

void Functions::saveChat()  
{
    buffer.push_back("Welcome to your server, use '@' for commands & '@help' for list of commands.\r\n"); 
    buffer.push_back(""); 
    buffer.push_back("...");  
}

void Functions::restoreChat(std::string input) 
{
    

    for (auto& a : buffer)    
    {
        std::cout << a << std::endl;     
    }
}



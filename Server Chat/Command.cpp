#include "Command.h"
#include "Server.h"
#include <iostream> 

 
// Instances
extern Server server; 

std::string Command::setCommandCase(std::string& commandCase)
{
    std::string returnMsg;

    if (commandCase == "@help")
    {
        returnMsg += "\033[2J\033[H";

        returnMsg += "Available Commands:  \n\n\n\033[G";

        returnMsg += "@exit - Clear console & revert back to chat.\n\n\033[G";

        returnMsg += "@register (username) (password) - register a user on the server. The server's response may indicate success, failure, or decline if the server's capacity is reached. \n\033[GParameters: username & password for account.\n\n\033[G";

        returnMsg += "@login - username password logs in user. \n\033[GParameters: username & password from user.\n\n\033[G";

        returnMsg += "@getlist – provides list of active clients, that are currently logged in and to transmit it to the client who initiated the request. \n\033[GParameters: none\n\n\033[G";

        returnMsg += "@logout - handles user disconnection. \n\033[GParameters: none\n\n\033[G";

        returnMsg += "@getlog - provides the content of the log file that includes the public messages to the client who initiated the request. \n\033[GParameters: none\n\n\033[G";

        returnMsg += "@send username message – overrides messages being sent to all users, user with command can send to desired users. \n\033[GParameters: message & username of desired receiver\n\n\033[G";

        returnMsg += "@help - provides active clients with the list of available commands on the server. \n\033[GParameters: none\n\033[G"; 
    }

    if (commandCase == "@exit")   
    {
        returnMsg += "\033[2J\033[H \033[G";   
    }

    if (commandCase.substr(0, 9) == "@register")
    {
           
        std::string username = "";
        std::string password = "";
        std::istringstream ss(commandCase);
        std::string command;

        // Split up
        ss >> command >> username;
        getline(ss, password); 

        // Trim
        if (!password.empty() && password[0] == ' ') 
        {
            password.erase(0, 1);
        }

            // Check 
            if (username.empty() || password.empty()) 
            {
                returnMsg += "\nInvalid input, password & username are required.";
                return returnMsg; 
            }

            // Check for spaces 
            if (username.find(' ') != string::npos || password.find(' ') != string::npos) 
            {
                returnMsg += "Invalid input, password & username cannot contain spaces.\n\n\033[G"; 
                return returnMsg;  
            }

            // Server's capacity is reached 
            if (server.chatCapacity < server.users)   
            {
                // At capacity message to GUI & server
                // Handle new user coming in
                std::cout << "Chat at full capacity. User '" << server.clientSocket << " 'should try again later to register." << std::endl;
                returnMsg += "\nChat is currently full, registration failed. Please try again later.\n\n\033[G ";  
                return returnMsg; 
            }
                // Get username 
            if (usersSignUp.find(username) != usersSignUp.end())  
            {
                returnMsg += "Username already exist!\n\n\033[G "; 
                return returnMsg; 
            } 

            // Add
            usersSignUp[username] = password;  
            returnMsg += "Registration successful!\n\n\033[G "; 
    }




    return returnMsg; 
}















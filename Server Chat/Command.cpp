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
        returnMsg += "Available Commands:";

        returnMsg += "@clear - Clear console.";

        returnMsg += "@register (username) (password) - register a user on the server. The server's response may indicate success, failure, or decline if the server's capacity is reached.";

        returnMsg += "@login - username password logs in user.";

        returnMsg += "@getlist � provides list of active clients, that are currently logged in and to transmit it to the client who initiated the request.";

        returnMsg += "@logout - handles user disconnection.";

        returnMsg += "@getlog - provides the content of the log file that includes the public messages to the client who initiated the request.";

        returnMsg += "@send username message � overrides messages being sent to all users, user with command can send to desired users.";

        returnMsg += "@help - provides active clients with the list of available commands on the server."; 
    }

    if (commandCase == "@clear")   
    {
        system("cls"); 
    }

    if (commandCase.substr(0, 9) == "@register")
    {
           
   
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
                returnMsg += "Invalid input, password & username are required.";
                return returnMsg; 
            }

            // Check for spaces 
            if (username.find(' ') != string::npos || password.find(' ') != string::npos) 
            {
                returnMsg += "Invalid input, password & username cannot contain spaces."; 
                return returnMsg;  
            }

            // Server's capacity is reached 
            if (server.chatCapacity < server.users)   
            {
                // At capacity message to GUI & server
                // Handle new user coming in
                std::cout << "Chat at full capacity. User '" << server.clientSocket << " 'should try again later to register." << std::endl;
                returnMsg += "Chat is currently full, registration failed. Please try again later. ";  
                return returnMsg; 
            }
                // Get username 
            if (usersSignUp.find(username) != usersSignUp.end())  
            {
                returnMsg += "Username already exist! "; 
                return returnMsg; 
            } 

            // Add
            usersSignUp[username] = password;  
            saveUser();
            returnMsg += "Registration successful! ";  
            
    }




    return returnMsg; 
}

// Created function that will upload users info start of program
void Command::uploadUser()
{
    std::ifstream file("accounts.txt");

    if (file.is_open()) 
    {
        std::string username;
        std::string password; 

        // Take in file info (username, password)
        while (file >> username >> password)
        {
            usersSignUp[username] = password;
        }
        file.close(); 
    }
}

void Command::saveUser()
{
    std::ofstream file("accounts.txt"); 

    if (file.is_open())
    {
        for (auto a : usersSignUp) 
        {
            file << a.first << " " << a.second << std::endl; 
        }
        file.close(); 
    }
}















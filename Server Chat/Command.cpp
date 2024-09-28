#include "Command.h"
#include <iostream> 

void Command::setCommandCase(std::string& commandCase)    
{

	if (commandCase == "@help")  
	{
		// Clear Console 
		system("cls"); 

		std::cout << "@exit - Clear console. " << std::endl; 
		std::cout << '\n'; 

		std::cout << "@register username password - register a user on the server. The server's response may indicate success, failure, or decline if the server's capacity is reached. \nParameters: username for account" << std::endl; 
		std::cout << '\n'; 

		std::cout << "@login - username password logs in user. \nParameters: username & password from user" << std::endl; 
		std::cout << '\n';

		std::cout << "@getlist – provides list of active clients, that are currently logged in and to transmit it to the client who initiated the request. \nParameters: none" << std::endl; 
		std::cout << '\n';

		std::cout << "@logout - handles user disconnection. \nParameters: none" << std::endl;  
		std::cout << '\n';

		std::cout << "@getlog - provides the content of the log file that includes the public messages to the client who initiated the request. \nParameters: none" << std::endl; 
		std::cout << '\n';

		std::cout << "@send username message – overrides messages being sent to all users, user with command can send to desired users. \nParameters: message & username of desired receiver" << std::endl; 
		std::cout << '\n';

		std::cout << "@help - provides active clients with the list of available commands on the server. \nParameters: none" << std::endl; 
	}
	
	
		
}
















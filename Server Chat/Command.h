#pragma once
#include "Server.h" 
#include <unordered_map>
#include <fstream>



class Command
{
public:


	// Members
	std::string commandCase;
	std::vector<std::string> loggedIn; 
	std::unordered_map<std::string, std::string> usersSignUp;  
	std::unordered_map<SOCKET, std::string> socUserMap; 


	// Functions 
	std::string setCommandCase(std::string& commandCase);      

	void uploadUser(); 

	void saveUser();

	void uploadCommands(std::string cmd); 

	void uploadMessages(); 

};


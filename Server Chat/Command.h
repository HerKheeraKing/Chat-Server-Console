#pragma once
#include "Server.h" 
#include <unordered_map>
#include <fstream>



class Command
{
public:


	// Members
	std::string commandCase;
	std::string username = "";
	std::string password = "";  
	std::vector<std::string> loggedIn; 
	std::unordered_map<std::string, std::string> usersSignUp;          


	// Functions 
	std::string setCommandCase(std::string& commandCase);      

	void uploadUser(); 

	void saveUser();

};


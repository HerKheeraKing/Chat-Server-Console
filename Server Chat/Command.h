#pragma once
#include "Server.h" 
#include <unordered_map>



class Command
{
public:


	// Members
	std::string commandCase;
	std::unordered_map<std::string, std::string> usersSignUp;          


	// Functions 
	std::string setCommandCase(std::string& commandCase);      



};


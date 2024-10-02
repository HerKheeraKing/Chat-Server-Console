#pragma once
#include "Server.h"


//// Instances
//extern Server server; 
 

class Functions
{
public:

	// Memebers
	std::vector<std::string> buffer;   

	void TCPport();
	
	void chatCapacity();  

	void saveChat(); 
	
	void restoreChat(std::string input); 



};



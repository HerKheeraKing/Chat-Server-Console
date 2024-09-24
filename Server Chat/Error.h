#pragma once
#include "Server.h"

//#define _CRT_SECURE_NO_WARNINGS 
//#define _WINSOCK_DEPRECATED_NO_WARNINGS

// Error Defining 
enum ErrorCodes : int
{
	SUCCESS = 0, SHUTDOWN = 1, DISCONNECT = 2, 
	BIND_ERROR = 3, CONNECT_ERROR = 4, SETUP_ERROR = 5, 
	STARTUP_ERROR = 6, ADDRESS_ERROR = 7, PARAMETER_ERROR = 8, HOSTNAME_ERROR = 9 
};
 

class Error
{
public:

    // Functions 
    static void ErrorCode(int error); 




};

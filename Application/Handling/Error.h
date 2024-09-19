#pragma once
#include <WinSock2.h>
#include "stdint.h"
#include <iostream>
using namespace std; 

#define _CRT_SECURE_NO_WARNINGS 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

// Error Defining 
enum ErrorCodes
{
   SUCCESS = 0, SHUTDOWN = 1, DISCONNECT = 2,
   BIND_ERROR = 3, CONNECT_ERROR = 4, SETUP_ERROR = 5,
   STARTUP_ERROR = 6, ADDRESS_ERROR = 7, PARAMETER_ERROR = 8
};


class Server
{
    public:

    // Functions 
    void ErrorCode(ErrorCodes error);




};
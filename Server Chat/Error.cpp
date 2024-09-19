#include "Error.h"
#include <iostream> 



// Functions 
void Error::ErrorCode(int error) 
{
    switch (error)
    {
    case SUCCESS:
    case SHUTDOWN:
        break;

    case DISCONNECT:
        std::cout << "Messenger's connection was severed", "Disconnection";
        break;

    case BIND_ERROR:
        std::cout << "Server could not bind to port successfully.", "Server Error";
        break;

    case CONNECT_ERROR:
        std::cout << "Cannot connect to client/server.", "Connect Error";
        break;

    case SETUP_ERROR:
        std::cout << "Messenger encountered an error during setup.", "Setup Error";
        break;

    case ADDRESS_ERROR:
        std::cout << "Server's address not in valid dot notation.", "Client Error";
        break;

    case STARTUP_ERROR:
        std::cout << "Messenger failed in platform-specific startup.", "Startup Error";
        break;

    case PARAMETER_ERROR:
        std::cout << "Messenger buffer is not big enough for message received.", "Buffer Error";
        break;

    default:
        std::cout << "Messenger encountered an unknown error.", "Unknown Error";
        break;
    }
}

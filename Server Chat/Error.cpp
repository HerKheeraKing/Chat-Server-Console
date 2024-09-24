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
        std::cout << "Messenger's connection was severed. Disconnection" << std::endl;
        break;

    case BIND_ERROR:
        std::cout << "Server could not bind to port successfully. Server Error." << std::endl; 
        break;

    case CONNECT_ERROR:
        std::cout << "Cannot connect to client/server. Connect Error." << std::endl;
        break;

    case SETUP_ERROR:
        std::cout << "Messenger encountered an error during setup. Setup Error." << std::endl;
        break;

    case ADDRESS_ERROR:
        std::cout << "Server's address not in valid dot notation. Client Error." << std::endl;
        break;

    case STARTUP_ERROR:
        std::cout << "Messenger failed in platform-specific startup. Startup Error." << std::endl;
        break;

    case PARAMETER_ERROR:
        std::cout << "Messenger buffer is not big enough for message received. Buffer Error." << std::endl;
        break;

    case HOSTNAME_ERROR:
        std::cout << "Hostname is not set up correctly. Hostname Error." << std::endl;  
        break;

    default:
        std::cout << "Messenger encountered an unknown error. Unknown Error." << std::endl;
        break;
    }
}

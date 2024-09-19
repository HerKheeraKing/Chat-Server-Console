#Scope of project: 
The scope of the project is to create a chat server that allows up to four users to receive and send messages to each other. The users will be able to use commands to execute actions like creating a user account or using a help command to get assistance from the server instead of using an interface that communicates to the user through buttons and visual interactional components.

Features:
Welcome Message! 
Registration – users can create an account. 
Help – assistance provided through the server. 
Authentication - Login. 
Logging – content including public messages exported to the user upon request. 
Logout –exit
Messaging – users can communicate with each other. 
Online Users – list of users online provided through command.

Command Character:
@
 
Command Format: 
@help - provides active clients with the list of available commands on the server.
Parameters: none 

@register username password - register a user on the server. 
The server's response may indicate success, failure, or decline if the server's capacity is reached.
Parameters: username for account 

@login username password – logs in user. 
Parameters: username & password from user

@getlist – provides list of active clients, that are currently logged in and to transmit it to the client who initiated the request.
Parameters: none 

@logout - handles user disconnection.
Parameters: none 

@getlog - provides the content of the log file that includes the public 
messages to the client who initiated the request.
Parameters: none 

@send ‘username’ message – overrides messages being sent to all users, user with command can send to desired users. 
Parameters: message & username of desired receiver 

System Architecture: 
Chat server – the server handles establishing connections between clients & receiving messages from the users, then forwarding those messages to the receiving client. 
User – user can create account & chat with other users while keeping track of other users’ status using the program.  
Message Handler – handles processing the chat messages in ways like processing the message content, identifying the sender/recipient & delivering of messages to the clients. 
Client Handler – handles individual client message receiving & holding/storing client information including logs, client connection, account information. I believe it also handles clients using commands to access other resources within the program. 


<div align="center">
  <img src="Images/Project%20Diagram.png" alt="Project Diagram" width="500"/>
</div>



#LICENSE INFO
This source code is available for viewing only. Usage of the code in any form is prohibited without explicit permission. Please refer to the LICENSE file for more details.

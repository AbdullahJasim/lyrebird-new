
#include "Client.h"
using namespace std;

//Constructor, socket needs to be initialized here
//Fairly large constructor, should consider splitting into other functions
//POssibly create a shared class between client and server as most of these lines are repeated
Client::Client() {
	WSADATA wsaData;
	int iResult;

	//Initialize Winsock
	//The MAKEWORK function equests version 2.2 of Winsock
	//It assigns the highest version of Windows Sockets to the variable wsaData
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	//Check if the call failed, if so exit with error code 1
	if (iResult != 0) {
		cout << "Initializing Winsock failed" << endl;
		exit(1);
	}

	//Struct info: https://msdn.microsoft.com/en-us/library/ms737530%28v=VS.85%29.aspx?f=255&MSPPError=-2147217396
	//This struct will hold the info of the resulting call to get the server address
	struct addrinfo *result = NULL;

	//This struct will hold the actual data of the server's address, and will be used for the rest of the connection
	struct addrinfo *ptr = NULL;

	//This struct is only passed for the initial call as a parameter and the only one defined by the client
	struct addrinfo hints;

	//Reset the value of hints
	ZeroMemory(&hints, sizeof(hints));
	//Then set its parameters for this connection, here it will be using TCP connection
	hints.ai_family = AF_UNSPEC; //Address family
	hints.ai_socktype = SOCK_STREAM; //Socket type
	hints.ai_protocol = IPPROTO_TCP; //Protocol type
}

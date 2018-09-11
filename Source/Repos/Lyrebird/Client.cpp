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

	//Get server address and port
	//For here I am using local address, this should be replaced by the server's IP address
	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);

	//Check if getting the address failed, exit with error
	if (iResult != 0) {
		cout << "Getting the address failed" << endl;
		WSACleanup();
		exit(1);
	}

	//Set the initial value of the connection socket to invalid
	ConnectSocket = INVALID_SOCKET;

	//Assign the value obtained earlier to the ptr variable, since this will be the address struct we use from now on
	ptr = result;

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		//Create the socket with the obtained address
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		//Check if it failed, throw error
		if (ConnectSocket == INVALID_SOCKET) {
			cout << "Error connecting socket" << endl;
			WSACleanup();
			exit(1);
		}

		//Connect the socket to the server
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		//Check if connection failed, close socket and assign the variable an invalid socket value
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket == INVALID_SOCKET;
			continue;
		}

		break;
	}

	//Ideally should be trying the next address
	//But for this project simply free the resource before throwing the error
	freeaddrinfo(result);
	if (ConnectSocket == INVALID_SOCKET) {
		cout << "Unable to connect to server" << endl;
		WSACleanup();
		exit(1);
	}
}

int Client::sendData() {
	int recvbuflen = DEFAULT_BUFLEN;

	//Side note, char* sendbuf = "This is a test"; will throw an error, even though that is what is used in the example
	//That's because char* does not have a constant size, while char[] does
	//So I will be using char sendbuf[], should lead to the same result
	char sendbuf[] = "This is a test";

	int iResult;

	//Send initial buffer
	//The 0 parameter is for flags, need to check what flags are later on
	iResult = send(ConnectSocket, sendbuf, (int) strlen(sendbuf), 0);
	//char sendbuf2[] = "This is a second test";
	//iResult = send(ConnectSocket, sendbuf2, (int)strlen(sendbuf2), 0);
	if (iResult == SOCKET_ERROR) {
		cout << "Sending initial packet failed" << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return -1;
	}

	cout << "Bytes send: " << iResult << endl;

	//Shut down the connection for sending, as we will not be sending anymore for now
	//This will have to be removed for the actual project as the client will have to keep sending data
	//But this will need to be excuted sometime to safely close the sockets
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "Shutting down the client's socket failed" << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return -1;
	}
}

int Client::receiveData() {
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];

	int iResult;
	while (1) {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

		if (iResult > 0) {
			cout << "Bytes received: " << iResult << endl;
		} else if (iResult == 0) {
			cout << "Connection closed" << endl;
			return 0;
		} else {
			cout << "Client receive failed with error: " << WSAGetLastError() << endl;
			return -1;
		}
	}
}

int Client::disconnect() {
	int iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "Shutting down the clinet's socet failed" << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return -1;
	}

	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}
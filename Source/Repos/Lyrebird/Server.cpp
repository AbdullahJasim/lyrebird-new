#include "Server.h"

using namespace std;

//Much like the client class, the constructor is pretty long
//Some of the functions / lines are shared with the client and should be made available in a utility class for both classes
Server::Server() {
	WSADATA wsaData;
	int iResult;

	//Initialize Winsock, check for errors
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "Initializing Winsock failed" << endl;
		exit(1);
	}

	struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	//Note that a flag is added to the server's hints struct
	hints.ai_flags = AI_PASSIVE;

	//The address is passed as NULL here, as opposed to an actual address
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		cout << "Getting the address failed" << endl;
		WSACleanup();
		exit(1);
	}

	ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		cout << "Error with establishing listening socket" << endl;
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}

	//Need to bind a local address to a socket in here
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		cout << "Binding socket failed" << endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	//result address info is no longer needed after binding
	freeaddrinfo(result);

	//Listen to the socket
	//SOMAXCONN instructs the Winsock provider for this socket to allow a maximum reasonable number of pending connections in the queue
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		cout << "Listen failed with error: %ld\n" << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	//Accepting a socket
	//Normally this needs to be in a loop to continue accepting clients
	ClientSocket = INVALID_SOCKET;
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		cout << "Accept failed: " << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	closesocket(ListenSocket);
}

int Server::sendData(const char* recvbuf, int iResult) {
	return send(ClientSocket, recvbuf, iResult, 0);
}

int Server::receiveData() {
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
	int iResult, iSendResult;

	while (1) {
		//cout << "Server receiving" << endl;
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			cout << "Bytes received: " << iResult << endl;
			cout << recvbuf << endl;
			iSendResult = sendData(recvbuf, iResult);
			//iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				cout << "Sending data to client failed" << endl;
				closesocket(ClientSocket);
				WSACleanup();
				return -1;
			}
		}
		else if (iResult == 0) {
			//cout << "Closing connection" << endl;
		}
		else {
			cout << "Receiving data from client failed with error: " << WSAGetLastError() << endl;
			closesocket(ClientSocket);
			WSACleanup();
			return -1;
		}
	}

	return 0;
}

int Server::disconnect() {
	int iResult;

	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "Shutdown server failed: " << WSAGetLastError() << endl;
		closesocket(ClientSocket);
		WSACleanup();
		return -1;
	}

	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}
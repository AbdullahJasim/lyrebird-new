#include "ServerNetwork.h"

using namespace std;

const int DEFAULT_BUFFER_LENGTH = 512;
const PCSTR DEFAULT_PORT = "6881";

ServerNetwork::ServerNetwork() {
	WSADATA data;

	listeningSocket = INVALID_SOCKET;
	clientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL, hints;

	callRetValue = WSAStartup(MAKEWORD(2, 2), &data);
	if (callRetValue != 0) {
		cout << "Startup failed" << endl;
		exit(1);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	callRetValue = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (callRetValue != 0) {
		cout << "Getting address failed" << endl;
		WSACleanup();
		exit(1);
	}

	listeningSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listeningSocket == INVALID_SOCKET) {
		cout << "Setting up listening socket failed" << endl;
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}

	u_long mode = 0;

	callRetValue = ioctlsocket(listeningSocket, FIONBIO, &mode);
	if (callRetValue == SOCKET_ERROR) {
		cout << "Locking mode failed with : " << WSAGetLastError() << " error" << endl;
		closesocket(listeningSocket);
		WSACleanup();
		exit(1);
	}

	callRetValue = bind(listeningSocket, result->ai_addr, (int) result->ai_addrlen);
	if (callRetValue == SOCKET_ERROR) {
		cout << "Binding the socket failed with : " << WSAGetLastError() << " error" << endl;
		freeaddrinfo(result);
		closesocket(listeningSocket);
		WSACleanup();
		exit(1);
	}

	freeaddrinfo(result);

	callRetValue = listen(listeningSocket, SOMAXCONN);
	if (callRetValue == SOCKET_ERROR) {
		cout << "Listen failed with error " << WSAGetLastError() << " error" << endl;
		closesocket(listeningSocket);
		WSACleanup();
		exit(1);
	}
}

bool ServerNetwork::acceptNewClient(unsigned int &id) {
	//Ff client waiting, accept the connection and save the socket
	clientSocket = accept(listeningSocket, NULL, NULL);

	if (clientSocket != INVALID_SOCKET)	{

		//Insert new client into session id table
		sessions.insert(pair<unsigned int, SOCKET>(id, clientSocket));

		return true;
	}

	return false;
}

int ServerNetwork::receiveData(unsigned int clientId, char* receivingBuffer) {

	if (sessions.find(clientId) != sessions.end())  {
		SOCKET currentSocket = sessions[clientId];
		callRetValue = NetworkService::receiveMessage(currentSocket, receivingBuffer, MAX_PACKET_SIZE);

		if (callRetValue == 0) {
			cout << "Connection to client " << clientId << " closed";
			closesocket(currentSocket);
		}

		return callRetValue;
	}

	return 0;
}
#include "Server.h"

using namespace std;

unsigned int Server::clientId;

Server::Server() {
	WSADATA wsaData;
	int iResult;
	clientId = 0;

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
	hints.ai_flags = AI_PASSIVE;

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

	u_long iMode = 1;

	iResult = ioctlsocket(ListenSocket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR) {
		cout << "Changing socket mode to non-blocking failed" << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		exit(1);
	}

	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		cout << "Binding socket failed" << endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	freeaddrinfo(result);

	loadFiles();

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		cout << "Listen failed with error: %ld\n" << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}
}

void Server::loadFiles() {
	fa = new FileAccessor();
	su = new StringUtilities();
	files = fa->getLines(configFile);
}

void Server::update() {
	while (1) {
		//Each frame, the server will check for new clients and then it will listen to already connected clients
		ClientSocket = INVALID_SOCKET;
		ClientSocket = accept(ListenSocket, NULL, NULL);
		//If a new client is found, inser the mapping of its socket to the sessions table
		if (ClientSocket != INVALID_SOCKET) {
			sessions.insert(pair<unsigned int, SOCKET>(clientId, ClientSocket));
			clientId++;
		}

		receiveData();
	}

	exit(1);
}

int Server::sendData(SOCKET targetSocket, const char* recvbuf, int iResult) {
	//cout << "Sending" << endl;
	//In here, the server reads the encrypted files and sends some of them to clients
	/*
	The protocol that I want to use is as follows:
	1. Server reads the configuration file, which states the names of the files that have the encrypted tweets
	2. Since we have no information about the length of the tweets, or the number of the tweets, the server will send several packets in quick succession
	3. If the tweet can fit into a single buffer, we will terminate it with /n, otherwise do not terminate and send the rest via other packets
	4. If it is the end of the file, terminate with /n/n
	5. The server will send all of the lines for one file for one client
	6. Then the client will return the content in a similar manner, which means the server will keep listening to the same client until it's finished
	*/

	//All files have been sent already, no need to send more data
	//Might need to modify this to signal the clients to close their connections
	if (filesIndex >= files.size()) return 0;

	//Send the contents of the next file to the client
	//Change the contents of the files into a string
	string temp = (su->vectorToString(fa->getLines(files[filesIndex++])));
	const char* tempChar = temp.c_str();
	int buflen = DEFAULT_BUFLEN;

	cout << "Server sending" << tempChar << endl;

	return send(targetSocket, tempChar, buflen, 0);
}

int Server::receiveData() {
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
	int iResult, iSendResult;

	map<unsigned int, SOCKET>::iterator it;
	for (it = sessions.begin(); it != sessions.end(); it++) {
		ConnectSocket = it->second;
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

		if (iResult > 0) {
			iSendResult = sendData(ConnectSocket, recvbuf, iResult);
			if (iSendResult == SOCKET_ERROR) {
				cout << "Sending data to client failed" << endl;
				closesocket(ClientSocket);
				WSACleanup();
				return -1;
			}
		} else if (iResult == 0) {

		} else {
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
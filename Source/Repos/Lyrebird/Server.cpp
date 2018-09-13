#include "Server.h"

using namespace std;

unsigned int Server::clientId;

Server::Server() {
	WSADATA wsaData;
	int iResult;

	clientId = 0;
	filesIndex = 0;
	configFile = "config.txt";

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

int Server::sendData(unsigned int client, SOCKET targetSocket) {

	//All files have been sent already, no need to send more data
	//Might need to modify this to signal the clients to close their connections
	if (filesIndex >= files.size()) {
		//signalClientsToClose();
		//waitForAllResponses();
		//disconnect();
		return 0;
	}

	//Send the contents of the next file to the client
	//Change the contents of the files into a string
	string currentLine = files[filesIndex];

	vector<string> fileNames = su->splitLine(files[filesIndex]);

	int buflen = DEFAULT_BUFLEN;

	string temp = su->vectorToString(fa->getLines(fileNames[0]));
	char buffer[DEFAULT_BUFLEN] = {'\0'};

	temp.copy(buffer, temp.size(), 0);


	filesDistributed.insert(pair<unsigned int, string>(client, fileNames[1]));
	filesIndex++;

	//cout << "Server sending " << buffer << endl;

	return send(targetSocket, buffer, buflen, 0);
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
			cout << "Received packet from client" << endl;
			if (!su->wildcardCompare(recvbuf, "INITIATE_CONNECTION")) { //recvbuf != "INITIATE_CONNECTION") {
				cout << "Received decrypted string" << endl;
				vector<string> output = su->stringToVector(recvbuf);
				map<unsigned int, string>::iterator tempIt;
				tempIt = filesDistributed.find(it->first);
				fa->saveFile(output, tempIt->second);
			}

			iSendResult = sendData(it->first, ConnectSocket);
			if (iSendResult == SOCKET_ERROR) {
				cout << "Sending data to client failed" << endl;
				closesocket(ClientSocket);
				WSACleanup();
				return -1;
			}
		} else if (iResult == 0) {

		} else {
			//closesocket(ClientSocket);
			//WSACleanup();
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

void Server::signalClientsToClose() {
	//Once all files have been decrypted, send the string "TERMINATE_CONNECTION" to all clients
	//This signals to the cliens that they need to close their connections

	char endSignal[] = "TERMINATE_CONNECTION";

	map<unsigned int, SOCKET>::iterator it;
	for (it = sessions.begin(); it != sessions.end(); it++) {
		send(it->second, endSignal, 21, 0);
	}
}
#include "Server.h"

using namespace std;

const string CONFIG_FILE = "config.txt";
const string INIT_SIGNAL = "INITIATE_CONNECTION";
const char TERM_SIGNAL[] = "TERMINATE_CONNECTION";

//Constructor will setup the listening socket and load the files that need decryption
Server::Server() {
	WSADATA wsaData;
	int iResult;

	clients = 0;
	filesIndex = 0;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "Initializing Winsock failed" << endl;
		exit(1);
	}

	struct addrinfo *result = NULL;
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
		closesocket(ListenSocket);
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
	files = fa->getLines(CONFIG_FILE);
}

//Each frame listen to any new clients requesting a connection, add them to session map
//Then receive any data sent by already connected clients
void Server::update() {
	while (1) {
		SOCKET ClientSocket = INVALID_SOCKET;
		ClientSocket = accept(ListenSocket, NULL, NULL);

		if (ClientSocket != INVALID_SOCKET) {
			sessions.insert(pair<unsigned int, SOCKET>(clients, ClientSocket));
			clients++;
		}

		if (receiveData() == 0) return;
	}
}

//If all the files have already been sent, signal all clients to close their connection and return 0
//Otherwise, get the content of the next file and send it to the client
int Server::sendData(unsigned int client, SOCKET targetSocket) {
	if (filesIndex >= files.size()) {
		signalClientsToClose();
		waitForAllResponses();
		disconnect();
		return 0;
	}

	string currentLine = files[filesIndex];
	vector<string> fileNames = su->splitLine(files[filesIndex]);

	string temp = su->vectorToString(fa->getLines(fileNames[0]));
	char buffer[DEFAULT_BUFLEN] = {'\0'};
	temp.copy(buffer, temp.size(), 0);

	filesDistributed.insert(pair<unsigned int, string>(client, fileNames[1]));
	filesIndex++;

	return send(targetSocket, buffer, DEFAULT_BUFLEN, 0);
}

//Check all connected clients for sent data
//If the data the client has sent is not the initial connection then save the tweet into the mapped output file
int Server::receiveData() {
	char recvbuf[DEFAULT_BUFLEN];

	for (map<unsigned int, SOCKET>::iterator it = sessions.begin(); it != sessions.end(); it++) {
		SOCKET ConnectSocket = it->second;
		int iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);

		if (iResult > 0) {
			if (!su->wildcardCompare(recvbuf, INIT_SIGNAL)) {
				saveTweet(recvbuf, it->first);
			}

			int iSendResult = sendData(it->first, ConnectSocket);
			if (iSendResult == SOCKET_ERROR) {
				cout << "Sending data to client failed" << endl;
				closesocket(it->second);
				sessions.erase(it);
				clients--;
				WSACleanup();
				return -1;
			}

			if (iSendResult == 0) return 0;

			return iResult;
		}
	}

	return 1;
}

void Server::saveTweet(char tweet[], int client) {
	vector<string> output = su->stringToVector(tweet);
	map<unsigned int, string>::iterator tempIt;
	tempIt = filesDistributed.find(client);
	fa->saveFile(output, tempIt->second);
}

//Send termination signal to all connected clients
void Server::signalClientsToClose() {
	map<unsigned int, SOCKET>::iterator it;
	for (it = sessions.begin(); it != sessions.end(); it++) {
		send(it->second, TERM_SIGNAL, 21, 0);
	}
}

void Server::waitForAllResponses() {
	char recvbuf[DEFAULT_BUFLEN];

	map<unsigned int, SOCKET>::iterator it;

	while (1) {
		for (it = sessions.begin(); it != sessions.end(); it++) {
			int iResult = recv(it->second, recvbuf, DEFAULT_BUFLEN, 0);

			if (iResult > 0 && su->wildcardCompare(recvbuf, "TERMINATED")) {
					shutdown(it->second, SD_SEND);
					sessions.erase(it);
					clients--;
			}
		}

		if (clients == 0) {
			disconnect();
			return;
		}
	}
}

void Server::disconnect() {
	closesocket(ListenSocket);
	WSACleanup();
}
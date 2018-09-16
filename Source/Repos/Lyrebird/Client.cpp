#include "Client.h"

using namespace std;

const string INIT_SIGNAL = "INITIATE_CONNECTION";
const char TERM_SIGNAL[] = "TERMINATE_CONNECTION";

//Constructor will setup the connection socket to the server
Client::Client() {
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "Initializing Winsock failed" << endl;
		exit(1);
	}

	struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo(SERVER_ADDRESS, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		cout << "Getting the address failed" << endl;
		WSACleanup();
		exit(1);
	}

	ConnectSocket = INVALID_SOCKET;
	ptr = result;

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			cout << "Error connecting socket" << endl;
			WSACleanup();
			exit(1);
		}

		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket == INVALID_SOCKET;
			continue;
		}

		break;
	}

	freeaddrinfo(result);
	if (ConnectSocket == INVALID_SOCKET) {
		cout << "Unable to connect to server" << endl;
		WSACleanup();
		exit(1);
	}

	u_long iMode = 1;
	iResult = ioctlsocket(ConnectSocket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR) {
		cout << "Changing socket to non-blocking failed" << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		exit(1);
	}
}

//Each frame receive data from server
void Client::update() {
	sendData(INIT_SIGNAL);

	while (1) {
		if (receiveData() == 0) return;
	}
}

//If the server sends a termination signal, send a final signal back then disconnect
//Otherwise decrypt the message from the server and send it back
int Client::receiveData() {
	char recvbuf[DEFAULT_BUFLEN];

	while (1) {
		 int iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);

		if (iResult > 0) {
			if (StringUtilities::wildcardCompare(recvbuf, TERM_SIGNAL)) {
				send(ConnectSocket, "TERMINATED", 11, 0);
				disconnect();
				return 0;
			}

			vector<string> tweets = StringUtilities::stringToVector(recvbuf);
			vector<string> decryptedTweets = Decryptor::decryptTweets(tweets);
			string decryptedBuffer = StringUtilities::vectorToString(decryptedTweets);

			sendData(decryptedBuffer);
		}
	}
}

int Client::sendData(string data) {
	char sendbuf[DEFAULT_BUFLEN] = { '\0' };

	data.copy(sendbuf, data.size(), 0);

	int iResult = send(ConnectSocket, sendbuf, DEFAULT_BUFLEN, 0);
	if (iResult == SOCKET_ERROR) {
		cout << "Sending packet failed: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return -1;
	}
}

int Client::disconnect() {
	int iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "Shutting down the clinet's socket failed" << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return -1;
	}

	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}
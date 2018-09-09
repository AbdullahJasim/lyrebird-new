#include "ClientNetwork.h"

using namespace std;

const int DEFAULT_BUFFER_LENGTH = 512;
const PCSTR DEFAULT_PORT = "6881";

ClientNetwork::ClientNetwork() {
	WSADATA data;

	connectionSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	callRetValue = WSAStartup(MAKEWORD(2, 2), &data);

	if (callRetValue != 0) {
		cout << "Startup failed" << endl;
		exit(1);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	callRetValue = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (callRetValue != 0) {
		cout << "Getting address failed" << endl;
		WSACleanup();
		exit(1);
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		connectionSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (connectionSocket == INVALID_SOCKET) {
			cout << "Socket creation failed" << endl;
			WSACleanup();
			exit(1);
		}

		callRetValue = connect(connectionSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
		if (callRetValue == SOCKET_ERROR) {
			closesocket(connectionSocket);
			connectionSocket = INVALID_SOCKET;
			cout << "Connection to server failed" << endl;
		}
	}

	freeaddrinfo(result);
	if (connectionSocket == INVALID_SOCKET) {
		cout << "Unable to connect to server" << endl;
		WSACleanup();
		exit(1);
	}

	//Set socket to be blocking
	u_long mode = 1;

	callRetValue = ioctlsocket(connectionSocket, FIONBIO, &mode);
	if (callRetValue == SOCKET_ERROR) {
		cout << "Locking mode failed with : " << WSAGetLastError() << " error" << endl;
		closesocket(connectionSocket);
		WSACleanup();
		exit(1);
	}
}

int ClientNetwork::receivePackets(char* receivingBuffer) {
	callRetValue = NetworkService::receiveMessage(connectionSocket, receivingBuffer, MAX_PACKET_SIZE);

	if (callRetValue == 0) {
		cout << "Connection closed" << endl;
		closesocket(connectionSocket);
		WSACleanup();
		exit(1);
	}

	return callRetValue;
}
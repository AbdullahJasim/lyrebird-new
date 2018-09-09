#pragma once
#ifndef SERVER_NETWORK
#define SERVER_NETWORK

#include "NetworkService.h"
#include "NetworkData.h"

#include <ws2tcpip.h>
#include <map>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

class ServerNetwork {
public:
	ServerNetwork();
	~ServerNetwork();

	SOCKET listeningSocket;
	SOCKET clientSocket;

	int callRetValue;
	std::map<unsigned int, SOCKET> sessions;

	bool acceptNewClient(unsigned int &id);
	int receiveData(unsigned int clientId, char* receivingBuffer);
};

#endif
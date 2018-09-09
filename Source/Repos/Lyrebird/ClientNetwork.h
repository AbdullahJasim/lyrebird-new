#pragma once
#ifndef CLIENT_NETWORK
#define CLIENT_NETWORK

#include "NetworkService.h"
#include "NetworkData.h"

#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientNetwork {
public:
	int callRetValue;
	SOCKET connectionSocket;
	int receivePackets(char* receivingBuffer);

	ClientNetwork();
	~ClientNetwork();

private:
};

#endif
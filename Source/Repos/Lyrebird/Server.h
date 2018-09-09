#pragma once
#ifndef SERVER
#define SERVER

#include "ServerNetwork.h"

class Server {
public:
	Server();
	~Server();

	void update();

	void receiveFromClients();

private:
	static unsigned int CLIENT_ID;
	ServerNetwork* sn;
	char networkData[MAX_PACKET_SIZE];
};

#endif
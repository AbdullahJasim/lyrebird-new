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
	void sendActionPackets();

private:
	static unsigned int CLIENT_ID;
	ServerNetwork* sn;
	char networkData[MAX_PACKET_SIZE];
};

#endif
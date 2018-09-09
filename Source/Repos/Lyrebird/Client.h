#pragma once
#ifndef CLIENT
#define CLIENT

#include "ClientNetwork.h"

class Client {
public:
	Client();
	~Client();

	ClientNetwork* cn;
	char networkData[MAX_PACKET_SIZE];

	void update();
	void sendActionPackets();

private:
};

#endif

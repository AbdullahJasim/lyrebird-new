#pragma once
#ifndef SERVER
#define SERVER

#include "ServerNetwork.h"

class Server {
public:
	Server();
	~Server();

	void update();

private:
	static unsigned int CLIENT_ID;
	ServerNetwork* sn;
};

#endif
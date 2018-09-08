#pragma once
#ifndef CLIENT
#define CLIENT

#include "ClientNetwork.h"

class Client {
public:
	Client();
	~Client();

	ClientNetwork* cn;

private:
};

#endif

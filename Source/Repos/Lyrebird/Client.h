//Most networking code is taken from Microsoft's Winsock guide:
//https://docs.microsoft.com/en-us/windows/desktop/winsock/getting-started-with-winsock
#pragma once
#ifndef CLIENT
#define CLIENT

#include "Decryptor.h"
#include "StringUtilities.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 4096
#define SERVER_ADDRESS "127.0.0.1"

#pragma comment(lib, "Ws2_32.lib")

class Client {
public:
	Client();
	void update();

private:
	SOCKET ConnectSocket;
	Decryptor* decryptor;

	int sendData(std::string data);
	int receiveData();
	int disconnect();
};

#endif
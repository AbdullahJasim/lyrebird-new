//The server class will mirror the client class for the most part
#pragma once
#ifndef SERVER
#define SERVER

#include "FileAccessor.h"
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

#pragma comment(lib, "Ws2_32.lib")

class Server {
public:
	SOCKET ConnectSocket;

	//We need an additional socket here that will listen to all new client requests
	SOCKET ListenSocket;

	//Array for client socket
	SOCKET ClientSocket;

	Server();
	void update();
	int sendData(const char* recvbuf, int iResult);
	int receiveData();
	int disconnect();
};

#endif

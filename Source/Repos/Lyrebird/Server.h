//The server class will mirror the client class for the most part
#pragma once
#ifndef SERVER
#define SERVER

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

#pragma comment(lib, "Ws2_32.lib")

class Server {
public:
	SOCKET ConnectSocket;

	Server();
	int sendData();
	int receiveData();
	int disconnect();
};

#endif

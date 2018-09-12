//The server class will mirror the client class for the most part
#pragma once
#ifndef SERVER
#define SERVER

#include "FileAccessor.h"
#include "StringUtilities.h"
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <map>

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 4096

#pragma comment(lib, "Ws2_32.lib")

class Server {
public:
	SOCKET ConnectSocket;
	SOCKET ListenSocket;
	SOCKET ClientSocket;

	std::map<unsigned int, SOCKET> sessions;
	FileAccessor* fa;
	StringUtilities* su;
	std::string configFile = "config.txt";
	std::vector<std::string> files;
	int filesIndex = 0;

	Server();
	void update();
	int sendData(SOCKET targetSocket, const char* recvbuf, int iResult);
	int receiveData();
	int disconnect();

private:
	static unsigned int clientId;
	void loadFiles();
};

#endif

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
	std::map<unsigned int, std::string> filesDistributed;
	FileAccessor* fa;
	StringUtilities* su;
	std::string configFile;
	std::vector<std::string> files;
	int filesIndex;

	Server();
	void update();
	int disconnect();

private:
	int sendData(unsigned int client, SOCKET targetSocket);
	int receiveData();
	static unsigned int clientId;
	void loadFiles();
	void signalClientsToClose();
};

#endif

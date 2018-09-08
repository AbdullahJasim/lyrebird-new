#pragma once
#ifndef NETWORK_SERVICE
#define NETWORK_SERVICE

#include <winsock2.h>
#include <Windows.h>
#include <string>
#include <vector>

class NetworkService {
public:
	//Send function, will be sending a vector of strings, each as a line
	static int sendMessage(SOCKET currentSocket, char* message, int messageSize);

	//Receive function
	static int receiveMessage(SOCKET currentSocket, char* message, int bufferSize);

private:
	//Changes the vector of strings to a serialized string so it can be sent via winsock
	static char* serialize(std::vector<std::string> lines);

	//Changes a serialized message back to a vector of strings
	static std::vector<std::string> deserialize(char* serializedMessage);
};

#endif
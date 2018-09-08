#include "NetworkService.h"

using namespace std;

int NetworkService::sendMessage(SOCKET currentSocket, char* message, int messageSize) {
	//char* message = serialize(lines);

	return send(currentSocket, message, messageSize, 0);
}

int NetworkService::receiveMessage(SOCKET currentSocket, char* buffer, int bufferSize) {
	return recv(currentSocket, buffer, bufferSize, 0);
}

char* NetworkService::serialize(std::vector<std::string> lines) {

	return {};
}

std::vector<std::string> NetworkService::deserialize(char* serializedMessage) {

	return {};
}
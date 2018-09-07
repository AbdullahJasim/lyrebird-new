#include "NetworkService.h"

using namespace std;

int NetworkService::sendMessage(SOCKET currentSocket, std::vector<std::string> lines, int messageSize) {

	return 0;
}

int NetworkService::receiveMessage(SOCKET currentSocket, std::string buffer, int bufferSize) {
	return 0;
}

char* NetworkService::serialize(std::vector<std::string> lines) {

	return {};
}

std::vector<std::string> NetworkService::deserialize(char* serializedMessage) {

	return {};
}
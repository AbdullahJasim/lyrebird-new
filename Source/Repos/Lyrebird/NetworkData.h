#pragma once
#ifndef NETWORK_DATA
#define NETWORK_DATA

#define MAX_PACKET_SIZE 1000000

#include <string>

enum PacketTypes {
	INIT_CONNECTION = 0,
	ACTION_EVENT = 1
};

struct Packet {
	unsigned int packet_type;
	//std::vector<std::string> tweets;
	char* message;

	void serialize(char* data) {
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char* data) {
		memcpy(this, data, sizeof(Packet));
	}
};

#endif
#include "Client.h"

using namespace std;

Client::Client() {
	cn = new ClientNetwork();

	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.serialize(packet_data);
	NetworkService::sendMessage(cn->connectionSocket, packet_data, packet_size);
}

void Client::update() {
	Packet packet;
	int dataLength = cn->receivePackets(networkData);

	if (dataLength <= 0) {
		return;
	}

	int i = 0;
	while (i < (unsigned int) dataLength) {
		packet.deserialize(&(networkData[i]));
		i += sizeof(Packet);

		switch (packet.packet_type) {
		case ACTION_EVENT:
			cout << "Client received action event from server" << endl;
			sendActionPackets();
			break;

		default:
			cout << "Error in packet types" << endl;
			break;
		}
	}
}

void Client::sendActionPackets() {
	const unsigned int packetSize = sizeof(Packet);
	char packetData[packetSize];

	Packet packet;
	packet.packet_type = ACTION_EVENT;
	packet.serialize(packetData);

	NetworkService::sendMessage(cn->connectionSocket, packetData, packetSize);
}
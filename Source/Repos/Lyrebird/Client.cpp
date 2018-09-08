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
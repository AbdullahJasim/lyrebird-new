#include "Server.h"

using namespace std;

unsigned int Server::CLIENT_ID;

Server::Server() {
	CLIENT_ID = 0;
	sn = new ServerNetwork();
}

void Server::update() {
	if (sn->acceptNewClient(CLIENT_ID)) {
		cout << "Client " << CLIENT_ID << " has been connected to the server" << endl;
		CLIENT_ID++;
	}

	receiveFromClients();
}

void Server::receiveFromClients() {
	Packet packet;

	map<unsigned int, SOCKET>::iterator t;

	for (t = sn->sessions.begin(); t != sn->sessions.end(); t++) {
		int dataLength = sn->receiveData(t->first, networkData);

		if (dataLength <= 0) continue;

		int i = 0;
		while (i < (unsigned int) dataLength) {
			packet.deserialize(&(networkData[i]));
			i += sizeof(Packet);

			switch (packet.packet_type) {
			case INIT_CONNECTION:
				cout << "Server received initial packet from client" << endl;
				break;

			case ACTION_EVENT:
				cout << "Server received action event packet from client" << endl;
				break;

			default:
				cout << "Error in packet types" << endl;
				break;
			}
		}
	}
}
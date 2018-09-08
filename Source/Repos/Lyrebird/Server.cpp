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
}
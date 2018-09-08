#include "Decryptor.h"
#include "Server.h"
#include "Client.h"
#include <process.h>

using namespace std;

void serverLoop(void *);
void clientLoop(void);

Server* server;
Client* client;

int main() {
	server = new Server();

	_beginthread(serverLoop, 0, (void *)12);

	client = new Client();

	clientLoop();
	
	//Decryptor* d = new Decryptor;
	//d->decryptTweets("sample.txt", "output.txt");

	system("pause");
}

void serverLoop(void * arg) {
	while (1) {
		server->update();
	}
}

void clientLoop() {
	while (1) {

	}
}
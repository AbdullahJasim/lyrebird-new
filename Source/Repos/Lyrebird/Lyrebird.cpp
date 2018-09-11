#include "Decryptor.h"
#include "Server.h"
#include "Client.h"
#include <process.h>

using namespace std;

Server* server;
Client* client;
void serverLoop(void*);
void clientLoop(void*);

int main() {	
	//Decryptor* d = new Decryptor;
	//d->decryptTweets("sample.txt", "output.txt");

	_beginthread(serverLoop, 0, (void*)12);
	clientLoop((void*) 12);


	system("pause");
	return 0;
}

void serverLoop(void*) {
	server = new Server();
	server->receiveData();
}

void clientLoop(void*) {
	client = new Client();
	client->sendData();
	client->receiveData();
}
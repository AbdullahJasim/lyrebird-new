#include "Decryptor.h"
#include "Server.h"
#include "Client.h"
#include "StringUtilities.h"
#include <process.h>

using namespace std;

Server* server;
Client* client;
void serverLoop(void*);
void clientLoop(void*);

int main() {
	//Decryption test
	//Decryptor* d = new Decryptor;
	//d->decryptTweets("sample.txt", "output.txt");

	//Networking test
	//Need to look into CreatheThread instead to properly start and end threads
	_beginthread(serverLoop, 0, (void*)12);
	clientLoop((void*) 12);

	//String utilities test
	/*
	FileAccessor* fa = new FileAccessor();
	StringUtilities* su = new StringUtilities();

	string temp = (su->vectorToString(fa->getLines("sample.txt")));
	vector<string> tweets = (su->stringToVector(temp));

	cout << temp << endl;

	for (unsigned int i = 0; i < tweets.size(); i++) {
		cout << tweets[i] << " --- " << i << endl;
	}
	*/

	system("pause");
	return 0;
}

void serverLoop(void*) {
	//Establish socket
	server = new Server();
	server->update();
	//Listen to clients
	//server->receiveData();
}

void clientLoop(void*) {
	//Establish socket
	client = new Client();
	//Send initial buffer to server
	client->sendData();
	//Listen to data from server
	client->receiveData();
}
#include "Decryptor.h"
#include <process.h>

using namespace std;


int main() {	
	Decryptor* d = new Decryptor;
	d->decryptTweets("sample.txt", "output.txt");

	system("pause");
}
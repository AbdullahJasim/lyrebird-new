// Lyrebird.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Decryptor.h"

#include <iostream>

using namespace std;

int main() {
	FileAccessor* fa = new FileAccessor;
	Decryptor* d = new Decryptor;

	vector<string> tweets = fa->getLines("sample.txt");

	d->decryptTweets(tweets);

	//for (int i = 0; i < tweets.size(); i++) {
		//cout << "value of a: " << tweets[i] << endl;
	//}

	system("pause");
}
// Lyrebird.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "FileAccessor.h"

#include <iostream>

using namespace std;

int main() {
	FileAccessor* fa = new FileAccessor;

	vector<string> tweets = fa->getEncryptedTweets("sample.txt");

	for (int i = 0; i < tweets.size(); i++) {
		cout << "value of a: " << tweets[i] << endl;
	}

	system("pause");
}
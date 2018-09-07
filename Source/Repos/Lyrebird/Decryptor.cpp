#include "Decryptor.h"

#include <vector>
#include <string>

using namespace std;

vector<string> decryptTweets(vector<string> encryptedTweets) {
	//FileAccessor fa = new FileAccessor();

	vector<string> decryptedTweets;

	for (vector<string>::iterator t = encryptedTweets.begin(); t != encryptedTweets.end(); t++) {
		/*
		string tweet = t;
		tweet = removeExtraChars(tweet);
		int temp = int* getCipherNumber(tweet);
		temp = transformNumber(temp);
		tweet = decipherNumber(temp);

		decryptedTweets.push_back(tweet);
		*/
	}

	return decryptedTweets;
}
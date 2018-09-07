#include "FileAccessor.h"

#include <vector>

using namespace std;

ifstream* openTextFile(string fileName) {
	ifstream inputFile;

	inputFile.open(fileName);

	//File cannot be found / opened, return null
	if (!inputFile) {
		cout << "file cannot be opened";
		return 0;
	}

	return &inputFile;
}

/*
vector<string> parseEncryptedTweets(ifstream tweetsFile) {
	//The requirements for the assignment states that each tweet can be 1024 char long
	//There can be any number of tweets
	//I will however build this solution with the ability to parse any length
	vector<string> encryptedTweets;
	vector<char> currentTweet;

	char c;

	while (tweetsFile.get(c) != '\0') {
		currentTweet.push_back(c);

		while (tweetsFile.get(c) != '\n') {
			currentTweet.push_back(c);
		}

		encryptedTweets.push_back(currentTweet);
		currentTweet.clear();
	}

	return encryptedTweets;
}
*/


//string* getEncryptedTweets(string fileName) {
	/*ifstream inputFile = openTextFile(fileName);
	vector<string> tweets = parseEncryptedTweets(inputFile);
	inputFile.close();

	return tweets;
	*/
	//}

void saveTweets(string* tweets, string fileName) {

	return;
}
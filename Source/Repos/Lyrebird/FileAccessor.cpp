#include "FileAccessor.h"

#include <vector>

using namespace std;

int tweetsNumber = 0;

FileAccessor::FileAccessor() {

}

std::vector<std::string> FileAccessor::parseEncryptedTweets(std::ifstream& tweetsFile) {
	//The requirements for the assignment states that each tweet can be 1024 char long
	//There can be any number of tweets
	//I will however build this solution with the ability to parse any length
	vector<string> encryptedTweets;

	string line;

	while (getline(tweetsFile, line)) {
		encryptedTweets.push_back(line);
	}

	return encryptedTweets;
}


std::vector<std::string> FileAccessor::getEncryptedTweets(string fileName) {
	ifstream inputFile;

	inputFile.open(fileName);

	//File cannot be found / opened, return null
	if (!inputFile) {
		cout << "file cannot be opened\n";
		return {};
	}

	vector<string> tweets = parseEncryptedTweets(inputFile);

	inputFile.close();
	return tweets;
}

void FileAccessor::saveTweets(std::string* tweets, std::string fileName) {
	
	return;
}
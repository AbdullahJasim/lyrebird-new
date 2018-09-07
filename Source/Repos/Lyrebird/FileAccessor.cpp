#include "FileAccessor.h"

#include <vector>

using namespace std;

FileAccessor::FileAccessor() {

}

std::vector<std::string> FileAccessor::parseLines(std::ifstream& linesFile) {
	//The requirements for the assignment states that each tweet can be 1024 char long
	//There can be any number of tweets
	//I will however build this solution with the ability to parse any length
	vector<string> lines;

	string line;

	while (getline(linesFile, line)) {
		lines.push_back(line);
	}

	return lines;
}


std::vector<std::string> FileAccessor::getLines(string fileName) {
	ifstream inputFile;

	inputFile.open(fileName);

	//File cannot be found / opened, return null
	if (!inputFile) {
		cout << "file cannot be opened\n";
		return {};
	}

	vector<string> tweets = parseLines(inputFile);

	inputFile.close();
	return tweets;
}

void FileAccessor::saveTweets(std::string* tweets, std::string fileName) {
	
	return;
}
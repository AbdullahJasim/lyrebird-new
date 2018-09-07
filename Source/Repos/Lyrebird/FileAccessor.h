#pragma once
#pragma once
#ifndef FileAccessor
#define FileAccessor

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

//This class will handle the read / writing functions of files in the system
class FileAccessor {
public:
	//This function gets decrypted tweens from a file
	std::vector<std::string> getEncryptedTweets(std::string fileName);

	//This function takes a list of tweets and a filename and writes those tweets onto that file / destination
	void saveTweets(std::string* tweets, std::string fileName);

private:
	//Function that takes a file name / destination and returns the file in it
	std::ifstream openTextFile(std::string fileName);

	//This function takes a file and parses the encrypted tweets in it
	std::vector<std::string> parseEncryptedTweets(std::ifstream tweetsFile);
};

#endif
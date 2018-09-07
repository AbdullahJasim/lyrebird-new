#pragma once
#ifndef FILE_ACCESSOR
#define FILE_ACCESSOR

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

//This class handles the read / writing functions of files in the system
class FileAccessor {
public:
	//Gets lines from a file
	//Returns a vector of strings, each string being a line
	std::vector<std::string> getLines(std::string fileName);

	//Takes a list of tweets and a filename and writes those tweets onto that file / destination
	void saveFile(std::vector<std::string> lines, std::string fileName);

private:
	//Takes a file and parses the lines in it
	//Returns a vector of strings, each string being a line
	std::vector<std::string> parseLines(std::ifstream& tweetsFile);
};

#endif
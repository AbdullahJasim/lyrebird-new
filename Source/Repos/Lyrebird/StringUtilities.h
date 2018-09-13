#pragma once
#ifndef STRING_UTILITIES
#define STRING_UTILITIES

#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm> 
#include <cctype>


class StringUtilities {
public:
	std::string vectorToString(std::vector<std::string>);
	std::vector<std::string> stringToVector(std::string);
	std::vector<std::string> stringToVector(std::string input, std::string delim);
	std::vector<std::string> splitLine(std::string line);
	bool wildcardCompare(std::string input1, std::string input2);
	void trimLine(std::string &line);

private:
};

#endif
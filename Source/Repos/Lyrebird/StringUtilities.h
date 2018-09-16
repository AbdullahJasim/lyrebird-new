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
	//Takes a vector of strings, and implodes them into one large string separated by new line character
	static std::string vectorToString(std::vector<std::string>);

	//Takes a string and separates into multiple strings, separating by new line character
	static std::vector<std::string> stringToVector(std::string);

	//Takes a string and separates into multiple strings, separating by a specific delimiter
	static std::vector<std::string> stringToVector(std::string input, std::string delim);

	//Splits words, separated by space, in one line into multiple strings
	static std::vector<std::string> splitLine(std::string line);

	//Compares the first (given) part of two strings
	static bool wildcardCompare(std::string input1, std::string input2);
};

#endif
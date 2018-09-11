#pragma once
#ifndef STRING_UTILITIES
#define STRING_UTILITIES

#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>

class StringUtilities {
public:
	std::string vectorToString(std::vector<std::string>);
	std::vector<std::string> stringToVector(std::string);
private:
};

#endif
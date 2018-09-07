#pragma once
#ifndef Decrypt
#define Decrypt

#include "FileAccessor.h"

#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

//This class will handle all decryption functions of the decrypted tweets
class Decrypt {
public:
	std::vector<std::string> decryptTweets(std::vector<std::string> encryptedTweets);

private:
	//This function takes a string and removes every 8th character in it starting at the 8th char, as given in the requirements
	std::string removeExtraChars(std::string givenString);

	//This function takes every 6 chars and calculates them using base 41
	//The value for each char is provided via the requirements page
	//The formula is: valueofChar * (41^5 - positionOfChar)
	//For example, txdgac =  20 * 415 +24 * 414 + 4 * 413 + 7 * 412 + 1 * 411 + 3 * 410
	int* getCipherNumber(std::string givenString);

	//The numbers obtained via the cipher formula need to be mapped onto other numbers
	//The formula is C ^ d * (mod n)
	//C is the cipher value
	//d is a constant with the value of 1921821779
	//n is the constant 4294434817
	int* transformNumber(int* nums);

	//Using the inverse of the function used in getCipherNumbers, we need to obtain the text value
	std::string decipherNumbers(int* nums);
};

#endif
#pragma once
#ifndef DECRYPTOR
#define DECRYPTOR

#include "FileAccessor.h"

#include <cstdio>
#include <map>

//This class will handle all decryption functions of the decrypted tweets
class Decryptor {
public:
	//The main decrypt function, it takes the name of a file and returns the decrypted tweets
	std::vector<std::string> decryptTweets(std::string fileName);

private:
	//A helper function of the public interface
	std::vector<std::string> decryptTweets(std::vector<std::string> encryptedTweets);

	//This function takes a string and removes every 8th character in it starting at the 8th char, as given in the requirements
	void removeExtraChars(std::vector<std::string>& givenString);

	//This function takes every 6 chars and calculates them using base 41
	//The value for each char is provided via the requirements page
	//The formula is: valueofChar * (41^5 - positionOfChar)
	//For example, txdgac =  20 * 415 +24 * 414 + 4 * 413 + 7 * 412 + 1 * 411 + 3 * 410
	long long getCipherNumber(std::string givenString);

	//The numbers obtained via the cipher formula need to be mapped onto other numbers
	//The formula is C ^ d * (mod n)
	//C is the cipher value
	//d is a constant with the value of 1921821779
	//n is the constant 4294434817
	std::vector<long long> transformNumbers(std::vector<long long> nums);

	//Using the inverse of the function used in getCipherNumbers, we need to obtain the text value
	std::vector<char> decipherNumbers(std::vector<long long> nums);

	//This function reads a text file, and each first character in each line in that text file will have a value mapped to it that corresponds to its order
	//The file I use is named charValues.txt
	//This is so I can easily map values without having to hard code them into the program
	void getMappedValues(std::string fileName);

	//Function to use modular exponentiation formula to avoid excess runtime
	long long modularExponentiate(long long base, long long exponent, long long mod);

	//Gets a character from the map by its value
	char getCharacter(int x);
};

#endif
#pragma once
#ifndef DECRYPTOR
#define DECRYPTOR

#include "FileAccessor.h"

#include <algorithm> 
#include <cctype>
#include <locale>

#include <cstdio>
#include <map>

//This class handles all decryption functions
class Decryptor {
public:
	//The main decrypt function, it takes the name of a file and returns the decrypted tweets
	static std::vector<std::string> decryptTweets(std::string inputFile, std::string outputFile);

	//A helper function, takes the encrypted lines and returns the decrypted ones
	static std::vector<std::string> decryptTweets(std::vector<std::string> encryptedTweets);

private:
	//Remove every 8th character in a given string
	static void removeExtraChars(std::vector<std::string>& givenString);

	//Get the cipher number for each 6 characters
	static long long getCipherNumber(std::string givenString);

	//Get the transformed number of the cipher value
	//Takes a vector of numbers and returns another. Both vectors correspond to one tweet
	static std::vector<long long> transformNumbers(std::vector<long long> nums);

	//The inverse function of getCipherNumber
	//Returns one tweet per a vector of cipher values
	static std::vector<char> decipherNumbers(std::vector<long long> nums);

	//Reads a text file, and each first character in each line in that text file will have a value mapped to it that corresponds to its order
	static void getMappedValues(std::string fileName);

	//Function to use modular exponentiation formula to avoid excess runtime
	static long long modularExponentiate(long long base, long long exponent, long long mod);

	//Gets a character from the map by its value
	static char getCharacter(int x);

	//Trims the extra spaces at the end of a line
	static void trimLine(std::string &s);
};

#endif
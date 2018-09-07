#include "Decryptor.h"

#include <vector>
#include <string>

using namespace std;

const int SPACING = 8;
const int BASE_NUM = 41;
const long long EXPONENT = 1921821779;
const long long MOD = 4294434817;

map<char, int> VALUES_MAP;

void Decryptor::removeExtraChars(std::vector<std::string>& givenString) {
	for (unsigned int i = 0; i < givenString.size(); i++) {

		//Need to erase characters right to left to avoid erasing modified parts of the string
		//Set c to be the length of the string, then remove the extras after n * 8 character
		//Decrement c to account for 0th index
		int c = givenString[i].length();
		c -= (c % SPACING);
		c--;

		//Keep erasing every 8th character, using temporary variable to avoid damaging original variable
		while (c > 0) {
			string temp = givenString[i];
			temp.erase(c, 1);
			c -= SPACING;
			givenString[i] = temp;
		}
	}
}

std::vector<std::string> Decryptor::decryptTweets(std::vector<std::string> encryptedTweets) {
	//FileAccessor* fa;

	vector<string> decryptedTweets;
	removeExtraChars(encryptedTweets);

	for (vector<string>::iterator t = encryptedTweets.begin(); t != encryptedTweets.end(); t++) {
		cout << *t << endl;
		
		string tweet = *t;

		//Group the letters in a group of 6 and get the cipher value

		long long temp = getCipherNumber(tweet);
		//temp = transformNumber(temp);
		//tweet = decipherNumber(temp);

		//decryptedTweets.push_back(tweet);

	}

	return decryptedTweets;
}

long long Decryptor::getCipherNumber(std::string givenString) {
	long long result = 0;

	//If a character is not found within the text file, the function will return 0 for all of its group
	map<char, int>::iterator t;
	int place = 5;

	for (char & c : givenString) {
		if (c != '\0') {
			t = VALUES_MAP.find(c);
			if (t == VALUES_MAP.end()) continue;
			result += t->second * (long long) (pow(BASE_NUM, place));
			place--;
		} else {
			return 0;
		}
	}

	return result;
}

void Decryptor::getMappedValues(std::string fileName) {
	FileAccessor* fa = new FileAccessor;
	vector<string> values = fa->getLines(fileName);

	for (unsigned int i = 0; i < values.size(); i++) {
		VALUES_MAP.insert(pair<char, int>(values[i][0], i));
	}
}

std::vector<long long> Decryptor::transformNumber(std::vector<int> nums) {
	vector<long long> result;

	for (unsigned int i = 0; i < nums.size(); i++) {
		long long temp = modularExponentiate((long long) nums[i], EXPONENT, MOD);
		result.push_back(temp);
	}

	return result;
}

long long Decryptor::modularExponentiate(long long base, long long exponent, long long mod) {
	unsigned long long resultOne;
	unsigned long long resultTwo;

	if (exponent == 0) {
		//Base case 1: the power is 0, the result is 1 % mod
		return (1 % mod);

	} else if (exponent == 1) {
		//Base case 2: the power is 1, the result is base % mod
		return (base % mod);

	} else if ((exponent % 2) == 0) {
		//Recursive case 1: the power is even, recrusive call using half the power
		resultOne = modularExponentiate(base, exponent / 2, mod);
		resultOne = (resultOne * resultOne) % mod;
		return resultOne;

	} else {
		//Recusrive case 2: the power is odd, split it into base case 1 and recursive case 1
		resultOne = modularExponentiate(base, 1, mod);
		resultTwo = modularExponentiate(base, exponent - 1, mod);
		resultOne = (resultOne * resultTwo) % mod;
		return resultOne;
	}
}
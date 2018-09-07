#include "Decryptor.h"

#include <vector>
#include <string>

using namespace std;

const int SPACING = 8;
const int BASE_NUM = 41;
const long long EXPONENT = 1921821779;
const long long MOD = 4294434817;

map<char, int> VALUES_MAP;

std::vector<std::string> Decryptor::decryptTweets(std::string fileName) {
	FileAccessor* fa = new FileAccessor;
	vector<string> tweets = fa->getLines("sample.txt");
	return decryptTweets(tweets);
}

std::vector<std::string> Decryptor::decryptTweets(std::vector<std::string> encryptedTweets) {
	vector<string> decryptedTweets;

	removeExtraChars(encryptedTweets);
	getMappedValues("charValues.txt");

	for (vector<string>::iterator t = encryptedTweets.begin(); t != encryptedTweets.end(); t++) {
		string tweet = *t;
		vector<long long> cipherValues;

		//Group the letters in a group of 6 and get the cipher value
		//Will not be checking for a null exception here as the length of each tweet is guaranteed to have length of a multiple of 6
		int i = 0;
		char group[6];
		while (i < tweet.length()) {
			if (i < tweet.length()) group[0] = tweet[i];
			group[1] = tweet[i + 1];
			group[2] = tweet[i + 2];
			group[3] = tweet[i + 3];
			group[4] = tweet[i + 4];
			group[5] = tweet[i + 5];
			i += 6;

			long long temp = getCipherNumber(group);
			cipherValues.push_back(temp);
		}

		cipherValues = transformNumbers(cipherValues);

		vector<char> temp = decipherNumbers(cipherValues);
		tweet = string (temp.begin(), temp.end());

		cout << tweet << endl;
	}

	return decryptedTweets;
}

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

std::vector<char> Decryptor::decipherNumbers(std::vector<long long> nums) {	
	char group[6];
	vector<char> result;

	//Since it's only a group of 6, I decided to manually write each step
	//While it's more code, it's faster to run through
	for (unsigned int i = 0; i < nums.size(); i++) {
		long long temp = nums[i];

		long long remainder = temp % 41;
		group[5] = getCharacter((int) remainder);

		temp = temp / 41;
		remainder = temp % 41;
		group[4] = getCharacter((int)remainder);

		temp = temp / 41;
		remainder = temp % 41;
		group[3] = getCharacter((int)remainder);

		temp = temp / 41;
		remainder = temp % 41;
		group[2] = getCharacter((int)remainder);

		temp = temp / 41;
		remainder = temp % 41;
		group[1] = getCharacter((int)remainder);

		temp = temp / 41;
		remainder = temp % 41;
		group[0] = getCharacter((int)remainder);

		result.push_back(group[0]);
		result.push_back(group[1]);
		result.push_back(group[2]);
		result.push_back(group[3]);
		result.push_back(group[4]);
		result.push_back(group[5]);
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

char Decryptor::getCharacter(int x) {
	for (std::map<char, int>::iterator t = VALUES_MAP.begin(); t != VALUES_MAP.end(); t++) {
		if (t->second == x) {
			return t->first;
		}
	}
}

std::vector<long long> Decryptor::transformNumbers(std::vector<long long> nums) {
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
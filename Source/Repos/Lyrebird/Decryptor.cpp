#include "Decryptor.h"

#include <vector>
#include <string>

using namespace std;

map<char, int> valuesMap;

void Decryptor::removeExtraChars(std::vector<std::string>& givenString) {
	for (unsigned int i = 0; i < givenString.size(); i++) {

		//Need to erase characters right to left to avoid erasing modified parts of the string
		//Set c to be the length of the string, then remove the extras after n * 8 character
		//Decrement c to account for 0th index
		int c = givenString[i].length();
		c -= (c % 8);
		c--;

		//Keep erasing every 8th character, using temporary variable to avoid damaging original variable
		while (c > 0) {
			string temp = givenString[i];
			temp.erase(c, 1);
			c -= 8;
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

		int temp = getCipherNumber(tweet);
		//temp = transformNumber(temp);
		//tweet = decipherNumber(temp);

		//decryptedTweets.push_back(tweet);

	}

	return decryptedTweets;
}

int Decryptor::getCipherNumber(std::string givenString) {
	int result = 0;

	//If a character is not found within the text file, the function will return 0 for all of its group
	map<char, int>::iterator t;
	int place = 5;

	for (char & c : givenString) {
		if (c != '\0') {
			t = valuesMap.find(c);
			result += t->second * (pow(41.0, place));
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

	for (int i = 0; i < values.size(); i++) {
		valuesMap.insert(pair<char, int>(values[i][0], i));
		//cout << "value of a: " << values[i] << endl;
	}
}
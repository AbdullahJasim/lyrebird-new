#include "StringUtilities.h"

using namespace std;

string StringUtilities::vectorToString(vector<string> lines) {
	const char* delim = "\n";
	ostringstream imploded;

	copy(lines.begin(), lines.end(), ostream_iterator<string>(imploded, delim));

	return imploded.str();
}

vector<string> StringUtilities::stringToVector(string input) {
	cout << "Parsing " << input << endl;
	return stringToVector(input, "\n");
}

vector<string> StringUtilities::stringToVector(string input, string delim) {
	vector<string> results;
	string temp;

	size_t pos = input.find(delim);
	int i = 1;
	while (pos != string::npos) {
		temp = input.substr(0, pos);
		results.push_back(temp);
		input.erase(0, pos + delim.length());
		pos = input.find(delim);
	}

	return results;
}

vector<string> StringUtilities::splitLine(string line) {
	return stringToVector(line, " ");
}

bool StringUtilities::wildcardCompare (string input1, string input2) {
	int i = 0;

	while (input1.at(i) != '\0' && input2.at(i) != '\0') {
		if (input1.at(i) != input2.at(i)) {
			cout << "Comparing" << input1.at(i) << " and " << input2.at(i) << endl;
			//cout << "False" << endl;
			return false;
		}
		i++;
	}

	cout << "True" << endl;
	return true;
}
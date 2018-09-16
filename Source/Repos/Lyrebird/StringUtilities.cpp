#include "StringUtilities.h"

using namespace std;

string StringUtilities::vectorToString(vector<string> lines) {
	const char* delim = "\n";
	ostringstream imploded;

	copy(lines.begin(), lines.end(), ostream_iterator<string>(imploded, delim));

	return imploded.str();
}

vector<string> StringUtilities::stringToVector(string input) {
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
	vector<string> results;

	std::istringstream iss(line);
	for (std::string s; iss >> s; ) results.push_back(s);

	return results;
}

bool StringUtilities::wildcardCompare (string input1, string input2) {
	int i = 0;

	try {
		while (input1.at(i) != '\0' && input2.at(i) != '\0') {
			if (input1.at(i) != input2.at(i)) return false;

			i++;
		}
	}
	catch (out_of_range const& exc) {

	}

	return true;
}
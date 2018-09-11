#include "StringUtilities.h"

using namespace std;

string StringUtilities::vectorToString(vector<string> lines) {
	const char* delim = "\n";
	ostringstream imploded;

	copy(lines.begin(), lines.end(), ostream_iterator<string>(imploded, delim));

	return imploded.str();
}
vector<string> StringUtilities::stringToVector(string input) {
	vector<string> results;
	string delim = "\n";
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
#include "FileAccessor.h"

using namespace std;

std::vector<std::string> FileAccessor::parseLines(std::ifstream& linesFile) {
	//There can be any number of tweets, each with any length
	vector<string> lines;
	string line;

	while (getline(linesFile, line)) {
		lines.push_back(line);
	}

	return lines;
}


std::vector<std::string> FileAccessor::getLines(string fileName) {
	ifstream inputFile;

	inputFile.open(fileName);

	//File cannot be found / opened, return null
	if (!inputFile) {
		cout << "file cannot be opened\n";
		return {};
	}

	vector<string> lines = parseLines(inputFile);

	inputFile.close();
	return lines;
}

void FileAccessor::saveFile(std::vector<string> lines, std::string fileName) {
	ofstream outputFile;
	outputFile.open(fileName);

	for (int i = 0; i < lines.size(); i++) {
		outputFile << lines[i] << endl;
	}

	return;
}
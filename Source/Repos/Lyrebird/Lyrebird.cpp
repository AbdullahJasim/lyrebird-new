// Lyrebird.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "FileAccessor.h"

#include <iostream>

using namespace std;

int main() {
	FileAccessor* fa = new FileAccessor;

	string* tweets = fa->getEncryptedTweets("sample.txt");
	system("pause");
}
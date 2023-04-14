#pragma once


#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = filesystem;
class BannedWords {
private:
	vector<string> words;

public:
	BannedWords(const string dirPath);

	bool isBannedWord(const string word) const;

	string censorMiddleChar(const string word) const;

	string censorWord(string word) const;


};
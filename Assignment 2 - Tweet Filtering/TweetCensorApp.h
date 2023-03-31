#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include "TweetCensor.h"
#include "BannedWords.h"

using namespace std;
namespace fs = std::filesystem;

class TweetCensorApp {
private:
    const string tweetsDirPath;
    const string bannedWordsDirPath;
    const string censoredTweetsDirPath;

public:
    TweetCensorApp(const string tweetsDirPath, const string bannedWordsDirPath, const string censoredTweetsDirPath)
        : tweetsDirPath(tweetsDirPath), bannedWordsDirPath(bannedWordsDirPath), censoredTweetsDirPath(censoredTweetsDirPath) {}

    void run() const;
};


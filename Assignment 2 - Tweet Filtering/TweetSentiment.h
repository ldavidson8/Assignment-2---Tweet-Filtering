#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <vector>
#include "BannedWords.h"

namespace fs = std::filesystem;

class TweetSentiment {
public:
    TweetSentiment(const std::string tweetsDirPath, const std::string bannedWordsDirPath,
        const std::string posFilePath, const std::string negFilePath);
    void analyzeSentiment();
private:
    std::string tweetsDirPath;
    BannedWords bannedWords;
    std::vector<std::string> positiveWords;
    std::vector<std::string> negativeWords;
    std::vector<std::string> tweets;
};
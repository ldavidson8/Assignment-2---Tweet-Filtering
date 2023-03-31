#pragma once

#include <string>
#include "BannedWords.h"

class TweetCensor {
private:
	BannedWords bannedWords;

public:
	TweetCensor(const std::string bannedWordsDirPath);
	std::string censorTweet(std::string tweet) const;
};

#include "TweetCensor.h"
#include "BannedWords.h"

TweetCensor::TweetCensor(const std::string bannedWordsDirPath)
	: bannedWords(bannedWordsDirPath) {}

std::string TweetCensor::censorTweet(std::string tweet) const {
	std::istringstream iss(tweet);
	std::ostringstream oss;

	std::string word;
	while (iss >> word) {
		if (bannedWords.isBannedWord(word)) {
			oss << bannedWords.censorWord(word) << " ";
		}
		else {
			oss << word << " ";
		}
	}

	return oss.str();
}

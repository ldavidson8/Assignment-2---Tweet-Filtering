#include "TweetSentiment.h"
#include <fstream>
#include <algorithm>
#include <sstream>

TweetSentiment::TweetSentiment(const std::string& posFilePath, const std::string& negFilePath) :
    posFilePath(posFilePath), negFilePath(negFilePath) {}

int TweetSentiment::countSentimentWords(const std::string& tweet, const std::string& sentimentFilePath) const {
    std::ifstream file(sentimentFilePath);
    int count = 0;
    std::string word;
    while (file >> word) {
        if (tweet.find(word) != std::string::npos) {
            count++;
        }
    }
    return count;
}

std::string TweetSentiment::determineSentiment(int positiveCount, int negativeCount) const {
    if (positiveCount > negativeCount) {
        return "positive";
    }
    else if (negativeCount > positiveCount) {
        return "negative";
    }
    else {
        return "neutral";
    }
}

std::string TweetSentiment::analyze(const std::string& tweet) const {
    int positiveCount = countSentimentWords(tweet, posFilePath);
    int negativeCount = countSentimentWords(tweet, negFilePath);
    return determineSentiment(positiveCount, negativeCount);
}

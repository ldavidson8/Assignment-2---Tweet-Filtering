#pragma once
#include <string>

class TweetSentiment {
public:
    TweetSentiment(const std::string& posFilePath, const std::string& negFilePath);

    std::string analyze(const std::string& tweet) const;

private:
    int countSentimentWords(const std::string& tweet, const std::string& sentimentFilePath) const;
    std::string determineSentiment(int positiveCount, int negativeCount) const;

    std::string posFilePath;
    std::string negFilePath;
};
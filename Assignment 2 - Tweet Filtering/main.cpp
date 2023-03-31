#include <iostream>
#include "BannedWords.h"
#include "TweetCensorApp.h"

using namespace std;

int main() {
    const string tweetsDirPath = "tweets";
    const string bannedWordsDirPath = "banned_words";
    const string censoredTweetsDirPath = "censored_tweets";

    TweetCensorApp app(tweetsDirPath, bannedWordsDirPath, censoredTweetsDirPath);
    app.run();

    return 0;
}
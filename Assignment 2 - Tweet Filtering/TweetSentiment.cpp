#include "TweetSentiment.h"

TweetSentiment::TweetSentiment(const string tweetsDirPath, const string bannedWordsDirPath,
    const string posFilePath, const string negFilePath)
    : tweetsDirPath(tweetsDirPath), bannedWords(bannedWordsDirPath) {

    // Read in positive words from file
    ifstream posFile(posFilePath);
    string posWord;
    while (getline(posFile, posWord)) {
        transform(posWord.begin(), posWord.end(), posWord.begin(), ::tolower);
        positiveWords.push_back(posWord);
    }

    // Read in negative words from file
    ifstream negFile(negFilePath);
    string negWord;
    while (getline(negFile, negWord)) {
        transform(negWord.begin(), negWord.end(), negWord.begin(), ::tolower);
        negativeWords.push_back(negWord);
    }

    // Read in tweets from file
    for (const auto& entry : fs::directory_iterator(tweetsDirPath)) {
        if (entry.is_regular_file()) {
            ifstream file(entry.path());
            string tweet;
            while (getline(file, tweet)) {
                tweets.push_back(tweet);
            }
        }
    }
}

void TweetSentiment::analyzeSentiment() {
    for (const auto& tweet : tweets) {
        string censoredTweet = "";
        istringstream iss(tweet);
        string word;
        int positiveCount = 0;
        int negativeCount = 0;
        int neutralCount = 0;
        while (iss >> word) {
            string censoredWord = bannedWords.censorWord(word);
            if (censoredWord != word) {
                censoredTweet += censoredWord + " ";
            }
            else {
                censoredTweet += word + " ";
            }

            // Check if word is positive or negative
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (find(positiveWords.begin(), positiveWords.end(), word) != positiveWords.end()) {
                positiveCount++;
            }
            else if (find(negativeWords.begin(), negativeWords.end(), word) != negativeWords.end()) {
                negativeCount++;
            }
            else {
                neutralCount++;
            }
        }
        cout << "Tweet: " << tweet << endl;
        cout << "Censored tweet: " << censoredTweet << endl;
        cout << "Sentiment: ";
        if (positiveCount > negativeCount && positiveCount > neutralCount) {
            cout << "Positive";
        }
        else if (negativeCount > positiveCount && negativeCount > neutralCount) {
            cout << "Negative";
        }
        else {
            cout << "Neutral";
        }
        cout << endl << endl;
        cin.ignore();
    }
}

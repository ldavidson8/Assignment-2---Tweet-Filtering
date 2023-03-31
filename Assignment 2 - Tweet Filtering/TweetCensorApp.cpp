#include "TweetCensorApp.h"

void TweetCensorApp::run() const {
    const int maxLineLength = 80; // Maximum line length 80 characters
    TweetCensor tweetCensor(bannedWordsDirPath);

    for (const auto& entry : fs::directory_iterator(tweetsDirPath)) {
        if (entry.is_regular_file()) {
            ifstream inputFile(entry.path());
            ofstream outputFile(censoredTweetsDirPath + "/" + entry.path().filename().string());

            string tweet;
            cout << "Original Tweet:" << endl;
            while (getline(inputFile, tweet)) {
                // Limit line length to 80 characters
                int i = 0;
                while (i < tweet.length()) {
                    cout << tweet.substr(i, maxLineLength) << endl;
                    i += maxLineLength;
                }
            }
            cout << endl;
            inputFile.clear();
            inputFile.seekg(0);

            cout << "Censored Tweet:" << endl;
            while (getline(inputFile, tweet)) {
                string censoredTweet = tweetCensor.censorTweet(tweet);
                // Limit line length to 80 characters
                int i = 0;
                while (i < censoredTweet.length()) {
                    cout << censoredTweet.substr(i, maxLineLength) << endl;
                    outputFile << censoredTweet.substr(i, maxLineLength) << endl;
                    i += maxLineLength;
                }
            }
            cout << endl;

            inputFile.close();
            outputFile.close();

            // Prompt the user to press enter to continue to the next file
            cout << "Press enter to continue to the next tweet file" << endl;
            cin.ignore();
        }
    }

    cout << "Censoring completed!" << endl;
}

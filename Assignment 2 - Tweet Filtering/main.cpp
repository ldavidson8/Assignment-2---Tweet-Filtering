#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "BannedWords.h"
#include "TweetCensorApp.h"
#include "TweetSentiment.h"
#include <filesystem>

using namespace std;

const string tweetsDirPath = "tweets";
const string bannedWordsDirPath = "banned_words";
const string censoredTweetsDirPath = "censored_tweets";
const string posFilePath = "analysis/positive.txt";
const string negFilePath = "analysis/negative.txt";

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void printMenu() {
	cout << "What would you like to do?" << endl;
	cout << "1. Censor tweets" << endl;
	cout << "2. Analyze tweet sentiment" << endl;
	cout << "3. Quit" << endl;
}

void censorTweets() {
	TweetCensorApp app(tweetsDirPath, bannedWordsDirPath, censoredTweetsDirPath);
	app.run();
}

void analyzeSentiment() {
	TweetSentiment tweetSentiment(tweetsDirPath, bannedWordsDirPath, posFilePath, negFilePath);

	cout << "Analyzing tweet sentiment..." << endl;
	tweetSentiment.analyzeSentiment();
}


int main() {
	while (true) {
		printMenu();
		string userInput;
		getline(cin, userInput);
		if (userInput == "1") {
			censorTweets();
		}
		else if (userInput == "2") {
			analyzeSentiment();
		}
		else if (userInput == "3") {
			break;
		}
		else {
			cout << "Invalid input. Please try again." << endl;
		}
	}

	return 0;
}
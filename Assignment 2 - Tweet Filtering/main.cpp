#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "BannedWords.h"
#include "TweetCensorApp.h"
#include "TweetSentiment.h"
#include <filesystem>
#include <unordered_map>

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
	cout << "3. Find top 10 most frequent words" << endl;
	cout << "4. Quit" << endl;
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

void countWords(const string& tweetsDirPath) {
	unordered_map<string, int> wordCounts;
	for (const auto& entry : fs::directory_iterator(tweetsDirPath)) {
		if (entry.is_regular_file()) {
			ifstream file(entry.path());
			string tweet;
			while (getline(file, tweet)) {
				istringstream iss(tweet);
				string word;
				while (iss >> word) {
					transform(word.begin(), word.end(), word.begin(), ::tolower);
					wordCounts[word]++;
				}
			}
		}
	}

	vector<pair<string, int>> sortedWordCounts(wordCounts.begin(), wordCounts.end());
	auto comparePairsBySecond = [](const auto& p1, const auto& p2) {
		return p1.second > p2.second;
	};

	// Sort the vector of pairs by count
	sort(sortedWordCounts.begin(), sortedWordCounts.end(), comparePairsBySecond);

	cout << "Top 10 most frequent words:" << endl;
	for (int i = 0; i < 10 && i < sortedWordCounts.size(); i++) {
		cout << sortedWordCounts[i].first << ": " << sortedWordCounts[i].second << endl;
	}
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
			countWords(tweetsDirPath);
		}
		else if (userInput == "4") {
			break;
		}
		else {
			cout << "Invalid input. Please try again." << endl;
		}
	}

	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class BannedWords {
private:
	vector<string> words;

public:
	BannedWords(const string dirPath) {
		for (const auto& entry : fs::directory_iterator(dirPath)) {
			if (entry.is_regular_file()) {
				ifstream file(entry.path());
				string word;
				while (getline(file, word)) {
					transform(word.begin(), word.end(), word.begin(), ::tolower);
					words.push_back(word);
				}
			}
		}
	}

	bool isBannedWord(const string word) const {
		return find(words.begin(), words.end(), word) != words.end();
	}

	string censorWord(const string word) const {
		string censoredWord = "";
		for (int i = 0; i < word.size(); i++) {
			censoredWord += "*";
		}
		return censoredWord;
	}
};

class TweetCensor {
private:
	BannedWords bannedWords;

public:
	TweetCensor(const string bannedWordsDirPath) : bannedWords(bannedWordsDirPath) {}

	string censorTweet(const string tweet) const {
		stringstream ss(tweet);
		string word;
		string censoredTweet = "";
		while (ss >> word) {
			string lowerWord = word;
			transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
			if (bannedWords.isBannedWord(lowerWord)) {
				string censoredWord = bannedWords.censorWord(word);
				censoredTweet += censoredWord;
			}
			else {
				censoredTweet += word;
			}
			censoredTweet += " ";
		}
		return censoredTweet;
	}
};

class TweetCensorApp {
private:
	const string tweetsDirPath;
	const string bannedWordsDirPath;
	const string censoredTweetsDirPath;

public:
	TweetCensorApp(const string tweetsDirPath, const string bannedWordsDirPath, const string censoredTweetsDirPath)
		: tweetsDirPath(tweetsDirPath), bannedWordsDirPath(bannedWordsDirPath), censoredTweetsDirPath(censoredTweetsDirPath) {}

	void run() const {
		const int maxLineLength = 40; // Maximum line length 40 characters
		TweetCensor tweetCensor(bannedWordsDirPath);

		for (const auto& entry : fs::directory_iterator(tweetsDirPath)) {
			if (entry.is_regular_file()) {
				ifstream inputFile(entry.path());
				ofstream outputFile(censoredTweetsDirPath + "/" + entry.path().filename().string());

				string tweet;
				cout << "Original Tweet:" << endl;
				while (getline(inputFile, tweet)) {
					cout << tweet << endl;
				}
				cout << endl;
				inputFile.clear();
				inputFile.seekg(0);

				cout << "Censored Tweet:" << endl;
				while (getline(inputFile, tweet)) {
					string censoredTweet = tweetCensor.censorTweet(tweet);
					cout << censoredTweet << endl;
					outputFile << censoredTweet << endl;
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
};

int main() {
	// Change these paths to match your directory structure
	const string tweetsDirPath = "tweets";
	const string bannedWordsDirPath = "banned_words";
	const string censoredTweetsDirPath = "censored_tweets";

	TweetCensorApp app(tweetsDirPath, bannedWordsDirPath, censoredTweetsDirPath);
	app.run();

	return 0;
}	
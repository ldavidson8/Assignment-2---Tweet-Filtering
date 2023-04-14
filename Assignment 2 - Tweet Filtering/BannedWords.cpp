#include "BannedWords.h"

BannedWords::BannedWords(const string dirPath) {
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

bool BannedWords::isBannedWord(const string word) const {
    for (const auto& bannedWord : words) {
        if (word.find(bannedWord) != string::npos) {
            return true;
        }
    }
    return false;
}

string BannedWords::censorMiddleChar(const string word) const {
    string censoredWord = word;
    int length = word.length();
    int centerIndex = length / 2;
    if (length % 2 == 0) {
        censoredWord.replace(centerIndex - 1, 2, "**");
    }
    else {
        censoredWord.replace(centerIndex, 1, "*");
    }
    return censoredWord;
}

string BannedWords::censorWord(const string word) const {
    string censoredWord = word;
    for (const auto& bannedWord : words) {
        // Convert banned word to lowercase
        string bannedWordLowerCase = bannedWord;
        transform(bannedWordLowerCase.begin(), bannedWordLowerCase.end(), bannedWordLowerCase.begin(), ::tolower);
        size_t index = censoredWord.find(bannedWordLowerCase);
        while (index != string::npos) {
            // Replace middle character of banned word with '*'
            string censoredSubword = censorMiddleChar(bannedWord);
            censoredWord.replace(index, bannedWordLowerCase.length(), censoredSubword);
            // Check if there are more occurrences of banned word
            index = censoredWord.find(bannedWordLowerCase, index + censoredSubword.length());
        }
    }
    return censoredWord;
}
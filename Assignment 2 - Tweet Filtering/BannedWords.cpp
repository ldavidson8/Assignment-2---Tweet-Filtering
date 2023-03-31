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
    return find(words.begin(), words.end(), word) != words.end();
}

vector<string>::const_iterator BannedWords::begin() const {
    return words.begin();
}

vector<string>::const_iterator BannedWords::end() const {
    return words.end();
}

string BannedWords::censorWord(string word) const {
    int wordLength = word.length();
    int centerIndex = wordLength / 2;
    wordLength % 2 == 1
        ? word.replace(centerIndex, 1, "*") // Word length is odd, censor only the center character
        : word.replace(centerIndex - 1, 2, "**");// Word length is even, censor the two closest to the center
    return word;
}

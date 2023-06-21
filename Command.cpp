#include <fstream>
#include <vector>
#include "Command.h"
#include "IOFormatGuard.h"

Command::Command(std::istream& in, std::ostream& out, Dictionary& dict) :
    out_(out),
    dict_(dict),
    in_(in)
{}

void Command::help() const {
    IOFormatGuard guard(out_);
    out_ << "Available commands:\n" <<
    "help -- get this help message\n" <<
    "readFromFile <filename> -- read text from file\n" <<
    "printTable -- print 'word-frequency' table\n" <<
    "printFrequency <word> -- print frequency of word\n" <<
    "printTop <n> -- print n most frequent words\n" <<
    "printEnd <n> -- print n least frequent words\n" <<
    "printCount -- print unique words count\n" <<
    "delete <word> -- delete information about word\n" <<
    "enter -- enter text manually\n" <<
    "printCommand <filename> <command> -- print command output to file\n" <<
    "intersection <filename1> <filename2> -- read intersection of two files\n";
}

std::string Command::readTextFromFile(const std::string& filename) const {
    std::ifstream file(filename);
    std::ostringstream oss;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            oss << line << '\n';
        }
        file.close();
    } else {
        IOFormatGuard guard(out_);
        out_ << "Cannot open file: " << filename << "\n";
    }

    return oss.str();
}

std::vector<std::string> splitTextIntoWords(const std::string& text) {
    std::vector<std::string> words;
    std::istringstream iss(text);
    std::string word;

    while (iss >> word) {
        while (!word.empty() && !isalpha(word.back())) {
            word.pop_back();
        }

        if (!word.empty()) {
            words.push_back(word);
        }
    }

    return words;
}

void Command::readFromFile(const std::string& filename) {
    const std::string& text = readTextFromFile(filename);
    if (text.empty()) return;

    const std::vector<std::string>& words = splitTextIntoWords(text);
    for (const auto& word : words) {
        dict_.insert(word);
    }

    IOFormatGuard guard(out_);
    out_ << "Words from file successfully added\n";
}

void Command::printTable() const {
    const std::map<std::string, int>& table = dict_.getTable();
    IOFormatGuard guard(out_);

    if (table.empty()) {
        out_ << "Dictionary is empty\n";
        return;
    }

    for (const auto& [word, count] : table) {
        out_ << word << " -- " << count << "\n";
    }
}

void Command::printFrequency(const std::string& word) const {
    IOFormatGuard guard(out_);
    out_ << dict_.getCount(word);
}

std::multimap<int, std::string, std::greater<>> Command::getSortedTable() const {
    const std::map<std::string, int>& table = dict_.getTable();
    std::multimap<int, std::string, std::greater<>> sortedTable;

    for (const auto& [word, count] : table) {
       sortedTable.insert({count, word});
    }

    return sortedTable;
}

void Command::printTop(int n) const {
    const std::multimap<int, std::string, std::greater<>>& sortedTable = getSortedTable();
    IOFormatGuard guard(out_);

    if (sortedTable.empty()) {
        out_ << "Dictionary is empty\n";
        return;
    }

    auto it = sortedTable.begin();
    for (int i = 0; i < n && it != sortedTable.end(); i++, it++) {
        out_ << it->second << " -- " << it->first << "\n";
    }
}

void Command::printEnd(int n) const {
    const std::multimap<int, std::string, std::greater<>>& sortedTable = getSortedTable();
    IOFormatGuard guard(out_);

    if (sortedTable.empty()) {
        out_ << "Dictionary is empty\n";
        return;
    }

    auto it = sortedTable.rbegin();
    for (int i = 0; i < n && it != sortedTable.rend(); i++, it++) {
        out_ << it->second << " -- " << it->first << "\n";
    }
}

int Dictionary::getUniqueWordsCount() const {
    return uniqueWordsCount_;
}

void Command::printCount() const {
    IOFormatGuard guard(out_);
    out_ << "Unique words count: " << dict_.getUniqueWordsCount();
}
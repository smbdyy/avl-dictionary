#include <fstream>
#include <vector>
#include "Command.h"
#include "IOFormatGuard.h"

Command::Command(std::istream& in, std::ostream& out, Dictionary& dict) :
    out_(out),
    dict_(dict),
    in_(in)
{}

void Command::help() {
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
        out_ << "Cannot open file: " << filename << std::endl;
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

void Command::readFromFile(const std::string& filename) const {
    std::string text = readTextFromFile(filename);
    if (text.empty()) return;

    std::vector<std::string> words = splitTextIntoWords(text);
    for (const auto& word : words) {
        dict_.insert(word);
    }

    IOFormatGuard guard(out_);
    out_ << "Words from file successfully added";
}

void Command::printTable() {
    std::map<std::string, int> table = dict_.getTable();

}
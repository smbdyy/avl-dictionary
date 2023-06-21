#ifndef AVLDICTIONARY_COMMAND_H
#define AVLDICTIONARY_COMMAND_H

#include <iostream>
#include <string>
#include "Dictionary.h"

class Command {
public:
    Command(std::istream& in, std::ostream& out, Dictionary& dict);
    void help() const;
    void readFromFile(const std::string& filename);
    void printTable() const;
    void printFrequency(const std::string& word) const;
    void printTop(int n) const;
    void printEnd(int n) const;
    void printCount() const;
    void deleteWord(const std::string& word);
    void enterText();
    void intersection(const std::string& filename1, const std::string& filename2);
private:
    Dictionary dict_;
    std::ostream& out_;
    std::istream& in_;

    [[nodiscard]] std::string readTextFromFile(const std::string& filename) const;
    [[nodiscard]] std::multimap<int, std::string, std::greater<>> getSortedTable() const;
    [[nodiscard]] std::string readTextFromConsole() const;
    inline void addWordsFromText(const std::string& text);
    inline void addWords(const std::vector<std::string>& words);
};

#endif

#ifndef AVLDICTIONARY_COMMAND_H
#define AVLDICTIONARY_COMMAND_H

#include <iostream>
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
    void deleteWord();
    void enterText();
    void printCommandToFile();
    void intersection();
private:
    Dictionary dict_;
    std::ostream& out_;
    std::istream& in_;

    [[nodiscard]] std::string readTextFromFile(const std::string& filename) const;
    [[nodiscard]] std::multimap<int, std::string, std::greater<>> getSortedTable() const;
};

#endif

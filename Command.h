#ifndef AVLDICTIONARY_COMMAND_H
#define AVLDICTIONARY_COMMAND_H

#include <iostream>
#include "Dictionary.h"

class Command {
public:
    Command(std::istream& in, std::ostream& out, Dictionary& dict);
    void help();
    void readFromFile();
    void printTable();
    void printFrequency();
    void printTop();
    void printEnd();
    void printCount();
    void deleteWord();
    void enterText();
    void printCommandToFile();
    void intersection();
private:
    Dictionary dict_;
    std::ostream& out_;
    std::istream& in_;
};

#endif
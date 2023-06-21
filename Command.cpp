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
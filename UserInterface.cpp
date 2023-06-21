#include <sstream>
#include <fstream>
#include "UserInterface.h"

UserInterface::UserInterface(Command& commandInterface, std::istream& in, std::ostream& out) :
    commandInterface_(commandInterface),
    in_(in),
    out_(out)
{}

void UserInterface::run() {
    while (readCommandLine()) {}
}

void printInvalidCommandMessage() {
    std::cerr << "Invalid command\n";
}

bool UserInterface::readCommandLine() {
    std::string input;
    std::getline(in_, input);

    if (input == "exit") {
        return false;
    }

    std::istringstream iss(input);
    mapCommand(iss);
    return true;
}

void UserInterface::mapCommand(std::istringstream& iss) {
    mapCommand(iss, out_);
}

void UserInterface::mapCommand(std::istringstream& iss, std::ostream& printCommandOutput) {
    std::string command;
    if (!(iss >> command)) {
        printInvalidCommandMessage();
    }

    if (command == "help") {
        commandInterface_.help();
    }
    else if (command == "readFromFile") {
        callReadFromFileCommand(iss);
    }
    else if (command == "printTable") {
        commandInterface_.printTable(printCommandOutput);
    }
    else if (command == "printFrequency") {
        callPrintFrequencyCommand(iss, printCommandOutput);
    }
    else if (command == "printTop") {
        callPrintTopCommand(iss, printCommandOutput);
    }
    else if (command == "printEnd") {
        callPrintEndCommand(iss, printCommandOutput);
    }
    else if (command == "delete") {
        callDeleteWordCommand(iss);
    }
    else if (command == "enter") {
        commandInterface_.enterText();
    }
    else if (command == "printCommand") {
        callPrintCommandToFileCommand(iss);
    }
    else if (command == "intersection") {
        callIntersectionCommand(iss);
    }
}

void UserInterface::callReadFromFileCommand(std::istringstream& commandInputStream) {
    std::string filename;
    if (!(commandInputStream >> filename)) {
        printInvalidCommandMessage();
        return;
    }

    commandInterface_.readFromFile(filename);
}

void UserInterface::callPrintFrequencyCommand(std::istringstream& commandInputStream,
                                              std::ostream& printCommandOutput) {
    std::string word;
    if (!(commandInputStream >> word)) {
        printInvalidCommandMessage();
        return;
    }

    commandInterface_.printFrequency(printCommandOutput, word);
}

void UserInterface::callPrintTopCommand(std::istringstream& commandInputStream,
                                        std::ostream& printCommandOutput) {
    int n;
    if (!(commandInputStream >> n) || n <= 0) {
        printInvalidCommandMessage();
        return;
    }

    commandInterface_.printTop(printCommandOutput, n);
}

void UserInterface::callPrintEndCommand(std::istringstream& commandInputStream,
                                        std::ostream& printCommandOutput) {
    int n;
    if (!(commandInputStream >> n) || n <= 0) {
        printInvalidCommandMessage();
        return;
    }

    commandInterface_.printEnd(printCommandOutput, n);
}

void UserInterface::callDeleteWordCommand(std::istringstream& commandInputStream) {
    std::string word;
    if (!(commandInputStream >> word)) {
        printInvalidCommandMessage();
        return;
    }

    commandInterface_.deleteWord(word);
}

void UserInterface::callIntersectionCommand(std::istringstream& commandInputStream) {
    std::string filename1;
    std::string filename2;
    if (!(commandInputStream >> filename1)) {
        printInvalidCommandMessage();
        return;
    }

    if (!(commandInputStream >> filename2)) {
        printInvalidCommandMessage();
        return;
    }

    commandInterface_.intersection(filename1, filename2);
}

void UserInterface::callPrintCommandToFileCommand(std::istringstream& commandInputStream) {
    std::string filename;
    if (!(commandInputStream >> filename)) {
        printInvalidCommandMessage();
        return;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        out_ << "Cannot open file: " << filename << "\n";
        return;
    }

    mapCommand(commandInputStream);
}
#ifndef AVLDICTIONARY_USERINTERFACE_H
#define AVLDICTIONARY_USERINTERFACE_H

#include <iostream>
#include "Command.h"

class UserInterface {
public:
    UserInterface(Command& commandInterface, std::istream& in, std::ostream& out);
    void run();
private:
    Command& commandInterface_;
    std::istream& in_;
    std::ostream& out_;

    void printInvalidCommandMessage();
    bool readCommandLine();
    void mapCommand(std::istringstream& iss, std::ostream& printCommandOutput);
    void mapCommand(std::istringstream& iss);
    void callReadFromFileCommand(std::istringstream& commandInputStream);
    void callPrintFrequencyCommand(std::istringstream& commandInputStream, std::ostream& printCommandOutput);
    void callPrintTopCommand(std::istringstream& commandInputStream, std::ostream& printCommandOutput);
    void callPrintEndCommand(std::istringstream& commandInputStream, std::ostream& printCommandOutput);
    void callDeleteWordCommand(std::istringstream& commandInputStream);
    void callIntersectionCommand(std::istringstream& commandInputStream);
    void callPrintCommandToFileCommand(std::istringstream& commandInputStream);
};


#endif

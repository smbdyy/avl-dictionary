#include "Command.h"
#include "UserInterface.h"
#include "Dictionary.h"

int main() {
    Dictionary dict;
    Command command(std::cin, std::cout, dict);
    UserInterface userInterface(command, std::cin, std::cout);

    userInterface.run();
}
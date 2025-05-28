#include <iostream>
#include "userInterface.h"

int main() {
    auto * userinterface(new UserInterface);
    userinterface->run();
    return 0;
}
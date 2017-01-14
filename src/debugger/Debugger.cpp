#include "Debugger.h"
#include "../config.h"

void Debugger::out(std::string message) {
    if(DEBUG)
        std::cout << message << endl;
}
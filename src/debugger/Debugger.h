#ifndef GRAVEDIGGERS_DEBUGGER_H
#define GRAVEDIGGERS_DEBUGGER_H

#include <iostream>
#include <sstream>

class Debugger {

public:
    static void out(std::string);

    template <typename T> static std::string number(T number) {
        std::ostringstream ss;
        ss << number;
        return ss.str();
    }

};

#endif

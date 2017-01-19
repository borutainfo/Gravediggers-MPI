#include "Debugger.h"
#include "../config.h"
#include "../distributor/Distributor.h"

void Debugger::out(std::string message) {
    if(DEBUG) {
        if(Distributor::clock == 0)
            std::cout << Distributor::tid << " [no clk]: " << message << std::endl;
        else
            std::cout << Distributor::tid << " [" << Distributor::clock << " clk]: " << message << std::endl;
    }
}
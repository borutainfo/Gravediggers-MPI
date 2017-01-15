#ifndef GRAVEDIGGERS_CITYCOUNCIL_H
#define GRAVEDIGGERS_CITYCOUNCIL_H

#include "../entity/Corpse.h"
using namespace std;

class CityCouncil {
    int deathCounter;
    Corpses *corpses;

private:
    void generateNewDeadList();

public:
    CityCouncil();
    void publishDeadList();
    void goDoSomethingElse();
};

#endif
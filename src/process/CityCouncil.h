#ifndef GRAVEDIGGERS_CITYCOUNCIL_H
#define GRAVEDIGGERS_CITYCOUNCIL_H

#include "../entity/Corpse.h"

class CityCouncil {

private:
    int deathCounter;
    Corpses *corpses;

    void generateNewDeadList();

public:
    CityCouncil();
    void publishDeadList();
    void goDoSomethingElse();

};

#endif
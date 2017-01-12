#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
#ifndef GRAVEDIGGERS_MPI_CITYCOUNCIL_H
#define GRAVEDIGGERS_MPI_CITYCOUNCIL_H

#include "../autoload.h"
using namespace std;

class CityCouncil {
    int numberOfDeaths;
    list<Corpse*> *corpses;

private:
    void generateDeadList();

public:
    CityCouncil();
    void publishDeadList();
};

#endif

#pragma clang diagnostic pop
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "../config.h"
#include "../debugger/Debugger.h"
#include "../distributor/Distributor.h"
#include "CityCouncil.h"

CityCouncil::CityCouncil() {
    srand((unsigned int) time(NULL));
    this->deathCounter = 0;
    Debugger::out("Zarzad zostal wybrany");
}

void CityCouncil::generateNewDeadList() {
    this->corpses = new Corpses();
    int numberOfDeaths = MIN_NUMBER_OF_DEATHS + rand() % MAX_NUMBER_OF_DEATHS;
    for(int i = 1; i <= numberOfDeaths; i++) {
        this->corpses->push_back(new Corpse(this->deathCounter + i));
    }
    this->deathCounter += numberOfDeaths;
}

void CityCouncil::publishDeadList() {
    this->generateNewDeadList();
    int deathList[MAX_NUMBER_OF_DEATHS+1];
    int i = 0;
    deathList[i++] = corpses->size();
    for (Corpses::iterator corpse = corpses->begin(); corpse != corpses->end(); ++corpse)
        deathList[i++] = (*corpse)->getId();
    Distributor::broadcast(deathList, DEATH_LIST_PUBLICATION);
    Debugger::out("Zarzad wywiesil nowa liste zmarlych");
    std::cout << corpses->size() << std::endl;
}

void CityCouncil::goDoSomethingElse() {
    sleep(10);
}
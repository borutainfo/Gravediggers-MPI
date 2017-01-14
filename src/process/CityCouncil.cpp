#include <ctime>
#include <cstdlib>
#include "../config.h"
#include "../debugger/Debugger.h"
#include "CityCouncil.h"

CityCouncil::CityCouncil() {
    srand((unsigned int) time(NULL));
    this->deathCounter = 0;
    Debugger::out("Zarzad zostal wybrany");
}

void CityCouncil::generateNewDeadList() {
    this->corpses = new Corpses();
    int numberOfDeaths = MIN_NUMBER_OF_DEATHS + rand() % MAX_NUMBER_OF_DEATHS;
    cout << numberOfDeaths << endl;
    for(int i = 1; i <= numberOfDeaths; i++) {
        this->corpses->push_back(new Corpse(this->deathCounter + i));
    }
    this->deathCounter += numberOfDeaths;
}

void CityCouncil::publishDeadList() {
    this->generateNewDeadList();
    for (Corpses::iterator corpse = corpses->begin(); corpse != corpses->end(); ++corpse)
        cout << "grabaz nr " << (*corpse)->getId() << "\n";
}
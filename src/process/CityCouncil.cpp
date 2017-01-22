#include <cstdlib>
#include <unistd.h>
#include "CityCouncil.h"

#include "../debugger/Debugger.h"
#include "../distributor/Distributor.h"

CityCouncil::CityCouncil() {
    this->deathCounter = 0;
    Debugger::out("Zarzad zostal wybrany");
}

void CityCouncil::generateNewDeadList() {
    this->corpses = new Corpses();
    int numberOfDeaths = MIN_NUMBER_OF_DEATHS + (rand() % (MAX_NUMBER_OF_DEATHS - MIN_NUMBER_OF_DEATHS + 1));

    for(int i = 1; i <= numberOfDeaths; i++)
        this->corpses->push_back(new Corpse(this->deathCounter + i));

    this->deathCounter += numberOfDeaths;
}

void CityCouncil::publishDeadList() {
    this->generateNewDeadList();

    MultipleDataPacket packet;
    packet.size = this->corpses->size();
    int i = 0;

    for (Corpses::iterator corpse = corpses->begin(); corpse != corpses->end(); corpse++)
        packet.data[i++] = (*corpse)->getId();

    Distributor::broadcast(packet, DEATH_LIST_PUBLICATION);
    Debugger::out("Zarzad wywiesil nowa liste zmarlych (" + Debugger::number(corpses->size()) + ")");
}

void CityCouncil::goDoSomethingElse() {
    sleep(COUNCIL_SLEEP_TIME);
}
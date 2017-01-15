#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../config.h"
#include "../debugger/Debugger.h"
#include "../distributor/Distributor.h"
#include "FuneralHome.h"

FuneralHome::FuneralHome() {
    Debugger::out("Dom pogrzebowy zostal otwarty");
}

void FuneralHome::getDeathList() {
    int deathList[MAX_NUMBER_OF_DEATHS+1];
    Distributor::receive(deathList, CITY_COUNCIL, DEATH_LIST_PUBLICATION);
    int numberOfDeaths = deathList[0];
    this->availableCorpses = new Corpses();
    for(int i = 1; i <= numberOfDeaths; i++)
        this->availableCorpses->push_back(new Corpse(deathList[i]));
}

void FuneralHome::selectCorpse() {
    Corpse* selectedCorpse = this->availableCorpses->at(rand() % this->availableCorpses->size());
    Debugger::out("wybralem");
    std::cout << selectedCorpse->getId() << std::endl;
}
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "../config.h"
#include "../debugger/Debugger.h"
#include "../distributor/Distributor.h"
#include "FuneralHome.h"

FuneralHome::FuneralHome() {
    clock = 0;
    Debugger::out("Dom pogrzebowy zostal otwarty");
}

void FuneralHome::getDeathList() {
    clock++;
    int deathList[MAX_NUMBER_OF_DEATHS+1];
    Distributor::receive(deathList, CITY_COUNCIL, DEATH_LIST_PUBLICATION);
    int numberOfDeaths = deathList[0];
    this->availableCorpses = new Corpses();
    for(int i = 1; i <= numberOfDeaths; i++)
        this->availableCorpses->push_back(new Corpse(deathList[i]));
}

void FuneralHome::selectCorpse() {
    clock++;
    unsigned int selected = rand() % this->availableCorpses->size();
    corpse = availableCorpses->at(selected);
    availableCorpses->erase(availableCorpses->begin() + selected);
}

bool FuneralHome::makeAnOffer() {
    int ownOffer[2], competitorOffer[2];
    while(availableCorpses->size() > 0) {
        selectCorpse();
        int success = true;
        ownOffer[0] = clock;
        ownOffer[1] = corpse->getId();
        Distributor::broadcast(ownOffer, FUNERAL_OFFER);
        for (int i = 0; i < Distributor::size; i++) {
            if (i != Distributor::tid && i != CITY_COUNCIL) {
                Distributor::receive(competitorOffer, i, FUNERAL_OFFER);
                removeCorpseById(competitorOffer[1]);
                if (competitorOffer[1] == ownOffer[1] && (competitorOffer[0] < ownOffer[0] || (competitorOffer[0] == ownOffer[0] && i < Distributor::tid)))
                    success = false;
            }
        }
        if(success)
            return true;
    }
    return false;
}

void FuneralHome::removeCorpseById(int id) {
    for (Corpses::iterator corpse = availableCorpses->begin(); corpse != availableCorpses->end(); corpse++) {
        if ((*corpse)->getId() == id) {
            availableCorpses->erase(corpse);
            break;
        }
    }
}
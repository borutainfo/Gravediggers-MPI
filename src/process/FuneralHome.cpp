#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <algorithm>
#include "FuneralHome.h"
#include "../debugger/Debugger.h"
#include "../distributor/Distributor.h"

FuneralHome::FuneralHome() {
    Distributor::clock = 1;
    Debugger::out("Dom pogrzebowy zostal otwarty");
}

void FuneralHome::markCorpseAsUnavailable(int id) {
    for (Corpses::iterator corpse = this->availableCorpses->begin();
         corpse != this->availableCorpses->end(); corpse++) {
        if ((*corpse)->getId() == id) {
            this->availableCorpses->erase(corpse);
            break;
        }
    }
}

void FuneralHome::getDeathList() {
    this->availableCorpses = new Corpses();

    Distributor::MultipleDataPacket packet;
    Distributor::receive(packet, CITY_COUNCIL, DEATH_LIST_PUBLICATION);

    for (int i = 0; i < packet.size; i++)
        this->availableCorpses->push_back(new Corpse(packet.data[i]));
}

void FuneralHome::selectCorpse() {
    corpse = this->availableCorpses->at(rand() % this->availableCorpses->size());
    this->markCorpseAsUnavailable(corpse->getId());
}

bool FuneralHome::negotiate() {
    this->funeralsOrder.clear();

    bool result = true;
    Distributor::SingleDataPacket own, competitor;

    while (availableCorpses->size() > 0) {
        this->selectCorpse();

        own.clock = ++Distributor::clock;
        own.data = corpse->getId();

        Distributor::broadcast(own, FUNERAL_OFFER);

        for (int id = 0; id < Distributor::size; id++) {
            if (id != Distributor::tid && id != CITY_COUNCIL &&
                std::find(this->funeralsOrder.begin(), this->funeralsOrder.end(), id) == this->funeralsOrder.end()) {

                Distributor::receive(competitor, id, FUNERAL_OFFER);
                this->markCorpseAsUnavailable(competitor.data);

                Distributor::clock = std::max(own.clock, competitor.clock);
            }
        }
        this->funeralsOrder = Distributor::getOrder();
        Distributor::clock++;

        if (std::find(this->funeralsOrder.begin(), this->funeralsOrder.end(), Distributor::tid) !=
            this->funeralsOrder.end())
            return true;
    }
    return false;
}

void FuneralHome::makeFuneral() {
    Debugger::out("Zaklad pogrzebowy nr " + Debugger::number(Distributor::tid) + " robi pogrzeb zmarlemu nr " +
                  Debugger::number(corpse->getId()));
    sleep(FUNERAL_TIME);
}

void FuneralHome::meetWithOfficer() {

}
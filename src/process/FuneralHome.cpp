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

bool FuneralHome::checkFuneral(int tid) {
    return std::find(this->funerals.begin(), this->funerals.end(), tid) != this->funerals.end();
}

void FuneralHome::getDeathList() {
    this->availableCorpses = new Corpses();

    MultipleDataPacket packet;
    Distributor::receive(packet, CITY_COUNCIL, DEATH_LIST_PUBLICATION);
    Distributor::clock++;

    for (int i = 0; i < packet.size; i++) {
        this->availableCorpses->push_back(new Corpse(packet.data[i]));
    }
}

void FuneralHome::selectCorpse() {
    this->corpse = this->availableCorpses->at(rand() % this->availableCorpses->size());
    this->markCorpseAsUnavailable(corpse->getId());
}

bool FuneralHome::negotiate() {
    SingleDataPacket own, competitor;
    this->funerals.clear();

    while(this->funerals.size() != (Distributor::size-1) && this->availableCorpses->size() != 0) {
        if (!this->checkFuneral(Distributor::tid)) {
            this->selectCorpse();

            own.clock = ++Distributor::clock;
            own.data = corpse->getId();

            Distributor::broadcast(own, FUNERAL_OFFER);
        }

        for (int id = 0; id < Distributor::size; id++) {
            if (id != Distributor::tid && id != CITY_COUNCIL && !this->checkFuneral(id)) {

                Distributor::receive(competitor, id, FUNERAL_OFFER);
                this->markCorpseAsUnavailable(competitor.data);

                Distributor::clock = std::max(own.clock, competitor.clock);
            }
        }
        this->funerals = Distributor::getOrder();
        Distributor::clock++;
    }

    Distributor::clearSnapshot();
    return checkFuneral(Distributor::tid);
}

void FuneralHome::makeFuneral() {
    Distributor::clock++;
    Debugger::out("Zaklad pogrzebowy nr " + Debugger::number(Distributor::tid) + " robi pogrzeb zmarlemu nr " +
                  Debugger::number(this->corpse->getId()));
    sleep(FUNERAL_TIME);
}

void FuneralHome::meetWithOfficial() {
    SingleDataPacket token;
    int before = CITY_COUNCIL, after = CITY_COUNCIL;

    for (std::vector<int>::iterator tid = this->funerals.begin(); tid != this->funerals.end(); tid++) {
        if ((*tid) == Distributor::tid) {
            if(++tid != this->funerals.end())
                after = (*tid);
            break;
        }
        else {
            before = (*tid);
        }
    }

    if(before != CITY_COUNCIL) {
        Distributor::receive(token, before, OFFICIAL_TOKEN);
        Distributor::clock = std::max(Distributor::clock, token.clock);
        Distributor::clock++;
    }

    Distributor::clock++;
    Debugger::out("Zaklad pogrzebowy nr " + Debugger::number(Distributor::tid) + " ma spotkanie z urzednikiem. ");
    sleep(OFFICIAL_TIME);

    if(after != CITY_COUNCIL) {
        token.clock = ++Distributor::clock;
        token.data = 1;
        Distributor::send(token, after, OFFICIAL_TOKEN);
    }
}
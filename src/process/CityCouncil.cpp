#include "CityCouncil.h"

CityCouncil::CityCouncil() {
    this->numberOfDeaths = 0;
}

void CityCouncil::generateDeadList() {
    this->corpses = new list<Corpse*>;

    srand((unsigned int) time(NULL));

    int numberOfDeaths = MIN_NUMBER_OF_DEATHS + rand() % MAX_NUMBER_OF_DEATHS;

    for(int i = this->numberOfDeaths; i < this->numberOfDeaths + numberOfDeaths; i++) {
        this->corpses->push_back(new Corpse(i));
    }
    this->numberOfDeaths += numberOfDeaths;
}

void CityCouncil::publishDeadList() {
    this->generateDeadList();
    for(int i = 0; i < this->corpses->size(); i++) {
        cout << "grabaz nr " << this->corpses->front()->getId() << "\n";
    }
    cout << "mylist stores " << this->corpses->size() << " numbers.\n";
}
#ifndef GRAVEDIGGERS_FUNERALHOME_H
#define GRAVEDIGGERS_FUNERALHOME_H

#include "../entity/Corpse.h"

class FuneralHome {

private:
    unsigned int clock;
    Corpses *availableCorpses;
    void selectCorpse();
    void removeCorpseById(int id);

public:
    Corpse *corpse;
    FuneralHome();
    void getDeathList();
    bool makeAnOffer();

};

#endif

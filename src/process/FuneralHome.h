#ifndef GRAVEDIGGERS_FUNERALHOME_H
#define GRAVEDIGGERS_FUNERALHOME_H

#include "../entity/Corpse.h"

class FuneralHome {

private:
    Corpses *availableCorpses;

public:
    FuneralHome();
    void getDeathList();
    void selectCorpse();

};

#endif

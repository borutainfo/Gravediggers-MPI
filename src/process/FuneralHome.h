#ifndef GRAVEDIGGERS_FUNERALHOME_H
#define GRAVEDIGGERS_FUNERALHOME_H

#include "../entity/Corpse.h"

class FuneralHome {

private:
    Corpses *availableCorpses;
    std::vector<int> funeralsOrder;

    void selectCorpse();
    void markCorpseAsUnavailable(int id);

public:
    Corpse *corpse;

    FuneralHome();
    void getDeathList();
    bool negotiate();
    void makeFuneral();
    void meetWithOfficer();

};

#endif

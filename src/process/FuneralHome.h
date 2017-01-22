#ifndef GRAVEDIGGERS_FUNERALHOME_H
#define GRAVEDIGGERS_FUNERALHOME_H

#include "../entity/Corpse.h"

class FuneralHome {

private:
    Corpses *availableCorpses;
    std::vector<int> funerals;

    void selectCorpse();
    void markCorpseAsUnavailable(int id);
    bool checkFuneral(int tid);

public:
    Corpse *corpse;

    FuneralHome();
    void getDeathList();
    bool negotiate();
    void makeFuneral();
    void meetWithOfficial();

};

#endif

#ifndef GRAVEDIGGERS_CORPSE_H
#define GRAVEDIGGERS_CORPSE_H

#include <list>
using namespace std;

class Corpse {
    int id;

public:
    Corpse(int id);
    int getId();
};

typedef list<Corpse*> Corpses;

#endif

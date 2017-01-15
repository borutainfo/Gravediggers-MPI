#ifndef GRAVEDIGGERS_CORPSE_H
#define GRAVEDIGGERS_CORPSE_H

#include <vector>

class Corpse {
    int id;

public:
    Corpse(int id);
    int getId();
};

typedef std::vector<Corpse*> Corpses;

#endif

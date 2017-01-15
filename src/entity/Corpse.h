#ifndef GRAVEDIGGERS_CORPSE_H
#define GRAVEDIGGERS_CORPSE_H

#include <vector>
#include "../config.h"

class Corpse {
    int id;

public:
    Corpse(int id);
    int getId();
};

typedef std::vector<Corpse*> Corpses;

#endif

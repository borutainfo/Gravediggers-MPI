#ifndef GRAVEDIGGERS_DISTRIBUTORSTRUCTS_H
#define GRAVEDIGGERS_DISTRIBUTORSTRUCTS_H

#include "../config.h"

struct SingleDataPacket {
    int clock;
    int data;
};

struct MultipleDataPacket {
    int size;
    int data[MAX_ARRAY_SIZE];
};

struct SingleDataPacketSnapshot : SingleDataPacket {
    int tid;
    bool operator < (const SingleDataPacketSnapshot& rhs) const {
        return clock < rhs.clock || (clock == rhs.clock && tid < rhs.tid);
    }
};

#endif

#ifndef GRAVEDIGGERS_DISTRIBUTOR_H
#define GRAVEDIGGERS_DISTRIBUTOR_H

#include <vector>
#include "../config.h"

class Distributor {

public:
    static int tid, size, clock;

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

    static std::vector<SingleDataPacketSnapshot*> *snapshot;

    static void initialize();
    static void finalize();

    static bool identityCheck(int);

    static void makeSnapshot(SingleDataPacket, int);
    static std::vector<int> getOrder();

//    static void send(Packet &packet, int receiver, int tag = 0);
    static void send(SingleDataPacket &packet, int receiver, int tag = 0);
    static void send(MultipleDataPacket &packet, int receiver, int tag = 0);

//    static void broadcast(Packet &packet, int tag = 0);
    static void broadcast(SingleDataPacket &packet, int tag = 0);
    static void broadcast(MultipleDataPacket &packet, int tag = 0);

//    static void receive(Packet &packet, int sender, int tag = 0);
    static void receive(SingleDataPacket &packet, int sender, int tag = 0);
    static void receive(MultipleDataPacket &packet, int sender, int tag = 0);

};

#endif

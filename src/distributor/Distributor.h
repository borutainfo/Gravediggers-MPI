#ifndef GRAVEDIGGERS_DISTRIBUTOR_H
#define GRAVEDIGGERS_DISTRIBUTOR_H

#include <vector>
#include "DistributorStructs.h"

class Distributor {

public:
    static int tid, size, clock;
    static std::vector<SingleDataPacketSnapshot*> *snapshot;

    static void initialize();
    static void finalize();

    static bool identityCheck(int);

    static void makeSnapshot(SingleDataPacket, int);
    static void clearSnapshot();
    static std::vector<int> getOrder();

    static void send(SingleDataPacket &packet, int receiver, int tag = 0);
    static void send(MultipleDataPacket &packet, int receiver, int tag = 0);

    static void broadcast(SingleDataPacket &packet, int tag = 0);
    static void broadcast(MultipleDataPacket &packet, int tag = 0);

    static void receive(SingleDataPacket &packet, int sender, int tag = 0);
    static void receive(MultipleDataPacket &packet, int sender, int tag = 0);

};

#endif

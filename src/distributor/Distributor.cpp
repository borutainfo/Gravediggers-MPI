#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Distributor.h"

int Distributor::size, Distributor::tid, Distributor::clock = 0;
std::vector<Distributor::SingleDataPacketSnapshot*> *Distributor::snapshot =
        new std::vector<Distributor::SingleDataPacketSnapshot*>;

void Distributor::initialize() {
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &Distributor::size);
    MPI_Comm_rank(MPI_COMM_WORLD, &Distributor::tid);
    srand((unsigned int) time(NULL)+Distributor::tid);
}

void Distributor::finalize() {
    MPI_Finalize();
}

void Distributor::makeSnapshot(SingleDataPacket packet, int tid) {
    for (std::vector<SingleDataPacketSnapshot*>::iterator snapshot = Distributor::snapshot->begin();
         snapshot != Distributor::snapshot->end(); snapshot++) {
        if ((*snapshot)->tid == tid) {
            Distributor::snapshot->erase(snapshot);
            break;
        }
    }
    SingleDataPacketSnapshot *snapshot = new SingleDataPacketSnapshot();
    snapshot->tid = tid;
    snapshot->clock = packet.clock;
    snapshot->data = packet.data;
    Distributor::snapshot->push_back(snapshot);
}

std::vector<int> Distributor::getOrder() {
    std::vector<SingleDataPacketSnapshot> winners;
    for (std::vector<SingleDataPacketSnapshot*>::iterator snapshot1 = Distributor::snapshot->begin();
         snapshot1 != Distributor::snapshot->end(); snapshot1++) {
        bool status = true;
        for (std::vector<SingleDataPacketSnapshot*>::iterator snapshot2 = Distributor::snapshot->begin();
             snapshot2 != Distributor::snapshot->end(); snapshot2++) {
            if((*snapshot1)->tid == (*snapshot2)->tid)
                continue;
            if ((*snapshot1)->data == (*snapshot2)->data && ((*snapshot1)->clock > (*snapshot2)->clock ||
                    ((*snapshot1)->clock == (*snapshot2)->clock && (*snapshot1)->tid > (*snapshot2)->tid)))
                status = false;
        }
        if(status)
            winners.push_back(**snapshot1);
    }
    std::sort(winners.begin(), winners.end());
    std::vector<int> order;
    for (std::vector<SingleDataPacketSnapshot>::iterator winner = winners.begin(); winner != winners.end(); winner++) {
        order.push_back((*winner).tid);
    }
    Distributor::snapshot->clear();
    return order;
}

bool Distributor::identityCheck(int tid) {
    return tid == Distributor::tid;
}

//void Distributor::send(Packet &packet, int receiver, int tag) {
//    MPI_Send(&packet.clock, 1, MPI_INT, receiver, tag, MPI_COMM_WORLD);
//}

void Distributor::send(SingleDataPacket &packet, int receiver, int tag) {
    Distributor::makeSnapshot(packet, Distributor::tid);
    int message[2] = {packet.clock, packet.data};
    MPI_Send(&message, 2, MPI_INT, receiver, tag, MPI_COMM_WORLD);
}

void Distributor::send(MultipleDataPacket &packet, int receiver, int tag) {
    int message[MAX_ARRAY_SIZE + 1];
    message[0] = packet.size;
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        message[i+1] = packet.data[i];
    MPI_Send(&message, MAX_ARRAY_SIZE + 1, MPI_INT, receiver, tag, MPI_COMM_WORLD);
}

//void Distributor::broadcast(Packet &packet, int tag) {
//    for(int i = 0; i < Distributor::size; i++)
//        if(i != Distributor::tid && i != BROADCAST_EXCLUDED)
//            send(packet, i, tag);
//}

void Distributor::broadcast(SingleDataPacket &packet, int tag) {
    for(int i = 0; i < Distributor::size; i++)
        if(i != Distributor::tid && i != BROADCAST_EXCLUDED)
            send(packet, i, tag);
}

void Distributor::broadcast(MultipleDataPacket &packet, int tag) {
    for(int i = 0; i < Distributor::size; i++)
        if(i != Distributor::tid && i != BROADCAST_EXCLUDED)
            send(packet, i, tag);
}

//void Distributor::receive(Packet &packet, int sender, int tag) {
//    MPI_Status status;
//    MPI_Recv(&packet.clock, MAX_ARRAY_SIZE + 1, MPI_INT, sender, tag, MPI_COMM_WORLD, &status);
//}

void Distributor::receive(SingleDataPacket &packet, int sender, int tag) {
    MPI_Status status;
    int message[2];
    MPI_Recv(&message, MAX_ARRAY_SIZE + 1, MPI_INT, sender, tag, MPI_COMM_WORLD, &status);
    packet.clock = message[0];
    packet.data = message[1];
    Distributor::makeSnapshot(packet, sender);
}

void Distributor::receive(MultipleDataPacket &packet, int sender, int tag) {
    MPI_Status status;
    int message[MAX_ARRAY_SIZE + 1];
    MPI_Recv(&message, MAX_ARRAY_SIZE + 1, MPI_INT, sender, tag, MPI_COMM_WORLD, &status);
    packet.size = message[0];
    for(int i = 0; i < packet.size; i++)
        packet.data[i] = message[i+1];
}
#ifndef GRAVEDIGGERS_DISTRIBUTOR_H
#define GRAVEDIGGERS_DISTRIBUTOR_H

#include "iostream"
#include <mpi.h>
#include "typeinfo"

class Distributor {

private:
    static int tid, size;
    struct ObjectInfo {
        MPI_Datatype type;
        size_t size;
    };

    template <typename T> static ObjectInfo* getObjectInfo(T &data) {
        MPI_Datatype type = 0;
        ObjectInfo* objectInfo = new ObjectInfo;
        if (((std::string)typeid(T).name()).back() == 'c') {
            objectInfo->type = MPI_CHAR;
            objectInfo->size = sizeof(data) / sizeof(char);
        }
        else if (((std::string)typeid(T).name()).back() == 'i') {
            objectInfo->type = MPI_INT;
            objectInfo->size = sizeof(data) / sizeof(int);
        }
        return objectInfo;
    }

public:
    static void initialize();
    static void finalize();
    static bool identityCheck(int);

    template <typename T> static void send(T &data, int receiver, int tag = 0) {
        ObjectInfo* objectInfo = getObjectInfo(data);
        MPI_Send(&data, objectInfo->size, objectInfo->type, receiver, tag, MPI_COMM_WORLD);
    }

    template <typename T> static void broadcast(T &data, int tag = 0) {
        for(int i = 0; i < Distributor::size; i++)
            if(i != Distributor::tid)
                send(data, i, tag);
    }

    template <typename T> static void receive(T& data, int sender, int tag = 0) {
        ObjectInfo* objectInfo = getObjectInfo(data);
        MPI_Status status;
        MPI_Recv(&data, objectInfo->size, objectInfo->type, sender, tag, MPI_COMM_WORLD, &status);
    }
};

#endif

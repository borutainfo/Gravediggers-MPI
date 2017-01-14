#ifndef GRAVEDIGGERS_DISTRIBUTOR_H
#define GRAVEDIGGERS_DISTRIBUTOR_H

#include <mpi.h>
#include "../debugger/Debugger.h"
#include "typeinfo"

class Distributor {

private:
    static int tid, size;

public:
    static void initialize();
    static void finalize();
    static bool identityCheck(int);

    template <typename T> static void send(T data, int receiver, int tag = 0) {
        int size = sizeof(data);
        MPI_Datatype type = 0;
        if(size <= 1) {
            if (typeid(T) == typeid(char))
                type = MPI_CHAR;
            else if (typeid(T) == typeid(int))
                type = MPI_INT;
        }
        else {
            if (typeid(T) == typeid(char *))
                type = MPI_CHAR;
            else if (typeid(T) == typeid(int *))
                type = MPI_CHAR;
        }
        MPI_Send(&data, size, type, receiver, tag, MPI_COMM_WORLD);
    }

    template <typename T> static void receive(T *data, int sender, int tag = 0) {
        int size = sizeof(data);
        MPI_Datatype type = 0;
        MPI_Status status;
        if(size <= 1) {
            if (typeid(T) == typeid(char))
                type = MPI_CHAR;
            else if (typeid(T) == typeid(int))
                type = MPI_INT;
        }
        else {
            if (typeid(T) == typeid(char *))
                type = MPI_CHAR;
            else if (typeid(T) == typeid(int *))
                type = MPI_CHAR;
        }
        MPI_Recv(data, size, type, sender, tag, MPI_COMM_WORLD, &status);
    }
};

#endif

#include <cstdlib>
#include <ctime>
#include "Distributor.h"

int Distributor::size, Distributor::tid;

void Distributor::initialize() {
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &Distributor::size);
    MPI_Comm_rank(MPI_COMM_WORLD, &Distributor::tid);
    srand((unsigned int) time(NULL)+Distributor::tid);
}

void Distributor::finalize() {
    MPI_Finalize();
}

bool Distributor::identityCheck(int tid) {
    return tid == Distributor::tid;
}
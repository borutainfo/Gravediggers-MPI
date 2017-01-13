#include "autoload.h"
using namespace std;

CityCouncil *cityCouncil;

int main(int argc, char **argv) {
    cityCouncil = new CityCouncil();
    cityCouncil->publishDeadList();
    int size, rank, len;
    char processor[100];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(processor, &len);
    Corpse *corpse = new Corpse(1);
    printf("Hello world: %d of %d na (%s)\n", corpse->getId(), size, processor);

    MPI_Finalize();
}
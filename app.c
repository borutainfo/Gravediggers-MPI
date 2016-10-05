#include <mpi.h>
#include <stdio.h>
#define ROOT 0
#define MSG_TAG 100

int main(int argc, char **argv)
{
	int tid,size;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	printf("Checking!\n");
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &tid );
	printf("My id is %d from %d\n",tid, size);

	int msg[2];

	if ( tid == ROOT)
	{	int i;
		msg[0] = 1;
		MPI_Send( msg, 2, MPI_INT, 1, MSG_TAG, MPI_COMM_WORLD );
		printf("  ROOT Wyslalem %d %d do %d\n", msg[0], msg[1], 1);
		//for(i = 1; i < size; i++) {
			MPI_Recv(msg, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("  ROOT Otrzymalem %d %d od %d\n", msg[0], msg[1], status.MPI_SOURCE);
		//}
	}
	else
	{
		msg[1] = size;
		MPI_Recv(msg, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf(" Otrzymalem %d %d od %d\n", msg[0], msg[1], status.MPI_SOURCE);
		msg[0]++;
		if(tid+1 != size)
			MPI_Send( msg, 2, MPI_INT, tid+1, MSG_TAG, MPI_COMM_WORLD );
		else 
			MPI_Send( msg, 2, MPI_INT, ROOT, MSG_TAG, MPI_COMM_WORLD );
		printf(" Wyslalem %d %d do %d\n", msg[0], msg[1], ROOT );
	}

	MPI_Finalize();
}

#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	int size, rank, dest, source, count, tag=1;
	char inmsg;
	MPI_Status Stat;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int outmsg=rank;

	if (rank == 5) {
	  dest = 0;
	  source = 0;
	  MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	  //MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	}else{
	  dest = rank + 1;
	  source = 0;
	  //MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	}
    MPI_Recv(&inmsg, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);

    MPI_Get_count(&Stat, MPI_INT, &count);
	if (Stat.MPI_TAG == 1) printf("Task %d: Received %d int(s), value: %d, from task %d with tag %d \n",
		   rank, count, inmsg, Stat.MPI_SOURCE, Stat.MPI_TAG);
	MPI_Finalize();
}

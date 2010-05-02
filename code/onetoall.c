/**********************************************************************
 * Point-to-point communication using MPI
 *
 **********************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	int rank, size,i;
	double a;
	MPI_Status status;

	MPI_Init(&argc, &argv);               /* Initialize MPI               */
	MPI_Comm_size(MPI_COMM_WORLD, &size); /* Get the number of processors */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* Get my number                */

	/* Pass on */
	a = 999.999;
	if(rank != 0) //the first processor does not receive
		MPI_Recv(&a,1,MPI_DOUBLE,rank-1,rank-1,MPI_COMM_WORLD,&status);
	if(rank != size -1) //the last processor does not send
		MPI_Send(&a,1,MPI_DOUBLE,rank+1,rank,MPI_COMM_WORLD);
	if(rank != 0)
		printf("Processor %d got %f with label %d\n", rank,a,rank-1);

	MPI_Finalize(); 

	return 0;
}

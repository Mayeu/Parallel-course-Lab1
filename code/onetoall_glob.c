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

  /* Broadcast */
  a = 999.999;
  MPI_Bcast(&a,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
  printf("Processor %d got %f\n", rank,a);

  MPI_Finalize(); 

  return 0;
}

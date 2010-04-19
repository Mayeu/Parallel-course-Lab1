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
  
  /* Fan out */
  a = 999.999;
  int k = ceil(log2(size));
  int distance;
  for(i=0;i<k;i++){
    distance = pow(2,i);
    if(rank < distance && rank+distance < size)
      MPI_Send(&a,1,MPI_DOUBLE,rank+distance,rank,MPI_COMM_WORLD);
    else if(rank < 2*distance && rank-distance >= 0){
      MPI_Recv(&a,1,MPI_DOUBLE,rank-distance,rank-distance,MPI_COMM_WORLD,&status);
      printf("Processor %d got %f from %d\n",rank,a,rank-distance);
    }
  }

  MPI_Finalize(); 

  return 0;
}

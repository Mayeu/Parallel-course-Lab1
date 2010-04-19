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

  /* Broadcast 
  a = 999.999;
  MPI_Bcast(&a,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
  printf("Processor %d got %f\n", rank,a);
  */

  /* Pass on 
  a = 999.999;
  if(rank != 0) //the first processor does not receive
    MPI_Recv(&a,1,MPI_DOUBLE,rank-1,rank-1,MPI_COMM_WORLD,&status);
  if(rank != size -1) //the last processor does not send
    MPI_Send(&a,1,MPI_DOUBLE,rank+1,rank,MPI_COMM_WORLD);
  if(rank != 0)
    printf("Processor %d got %f with label %d\n", rank,a,rank-1);
  */

  /* Processor 0 send to all others
  if (rank == 0) {
    a=999.999;
    for (i=0;i<size;i++)
      MPI_Send(&a, 1, MPI_DOUBLE, i, 111, MPI_COMM_WORLD);
  } else {
    MPI_Recv(&a, 1, MPI_DOUBLE, 0, 111, MPI_COMM_WORLD, &status);
    printf("Processor %d got %f\n", rank,a);
  }*/

  MPI_Finalize(); 

  return 0;
}

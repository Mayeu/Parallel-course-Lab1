/**********************************************************************
 * A simple "hello world" program for MPI/C
 *
 **********************************************************************/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	int tmp;
	MPI_Init(&argc, &argv);               /* Initialize MPI               */
	MPI_Comm_rank(MPI_COMM_WORLD,&tmp);
	printf("My rank: %d\n",tmp);
	if(tmp == 0){
		MPI_Comm_size(MPI_COMM_WORLD,&tmp);
		printf("Size: %d\n",tmp);
	}
	printf("Hello World!\n");             /* Print a message              */

	MPI_Finalize();                       /* Shut down and clean up MPI   */

	return 0;
}

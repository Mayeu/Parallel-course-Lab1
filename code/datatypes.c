/**********************************************************************
 * Derived datatypes in MPI/C
 *
 **********************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int rank, size,nx,ny,row,col,count,blocklen,stride;
	double *A;
	MPI_Status status;
	MPI_Datatype newtype;

	MPI_Init(&argc, &argv);               /* Initialize MPI               */
	MPI_Comm_size(MPI_COMM_WORLD, &size); /* Get the number of processors */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* Get my number                */

	nx=100; ny=150;
	A=(double *)malloc(nx*ny*sizeof(double));
	for (row=0; row<nx;row++){
		for (col=0; col<ny;col++){
			//A[row*ny+col]=(double)col+1+(rank+1)*1000.0;
			A[row*ny+col] = (double)row*1000.0 + col;
			//printf("%d ",(int)A[row*ny+col]);
		}
		// printf("\n");
	}

	count=nx/2; blocklen=ny/2; stride=ny;
	MPI_Type_vector(count,blocklen,stride,MPI_DOUBLE,&newtype);
	MPI_Type_commit(&newtype);

	/* Send last column, notice the message length = 1 ! */
	if (rank == 0) {
		MPI_Send(&A[(nx/2)*ny+(ny/2)], 1, newtype, 1, 111, MPI_COMM_WORLD);

	} else if (rank==1) {
		MPI_Recv(&A[(nx/2)*ny], 1, newtype, 0, 111, MPI_COMM_WORLD, &status);
		for (row=nx/2; row<nx; row++){
			for(col=0;col<ny/2;col++)
				printf("%d ",(int)A[row*ny+col]);
			printf("\n");
		}
	}

	free(A);
	MPI_Type_free(&newtype);
	MPI_Finalize(); 

	return 0;
}

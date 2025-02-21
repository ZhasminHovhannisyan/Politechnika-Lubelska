#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int my_rank,p;
	int i,n; 
	double my_pi,pi,h,sum,x;

	if (argc<2)
	{
		printf("Correct use of the program: program number_of_integration_intervals\n");
		exit(1);
	}
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	if (my_rank==0)
		n=atoi(argv[1]);


	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

     	h=1.0/(double)n;

    /* Integration using the trapezoidal method */
	for (i=my_rank; i<n; i+=p)
	{
       		x=h*((double)i+0.5);
		sum+=4.0/(1.0+x*x);
	}
	my_pi=h*sum;

	MPI_Reduce(&my_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (my_rank == 0) 
		printf("pi=%.16f\n",pi);

	MPI_Finalize();
}
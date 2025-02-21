#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

#define min(x,y) (((x) < (y)) ? (x) : (y))

void print_matrix(int m, int k, double *M, char N) {
    int i, j;
    printf ("Top left corner of the matrix %c: \n", N);
    for (i=0; i<min(m,4); i++) {
      for (j=0; j<min(k,4); j++) {
        printf ("%12.0f", M[j+i*k]);
      }
      printf ("\n");
    }
}

int main (int argc, char *argv[]) {
    double *A, *B, *C;
    int m, n, k, i, j, l;
    double t;

    if (argc == 4) {
        m = atoi(argv[1]);
        k = atoi(argv[2]);
        n = atoi(argv[3]);
    } else {
        //m = 1000, k = 2000, n = 3000;
        printf("Correct call to matrix multiplication c[m][n]=a[m][k] * b[k][n]: ./mxm m k n\n");
        exit(1);
    }
    printf ("Allocating memory for a matrix C[%d][%d] = A[%d][%d] * B[%d][%d]\n", m, n, m, k, k, n);
    A=(double*)malloc(m*k*sizeof(double));
    B=(double*)malloc(k*n*sizeof(double));
    C=(double*)calloc(m*n,sizeof(double));

    printf("Memory requirements: %lf GB\n", (m*k+k*n+m*n)*sizeof(double)/1000000000.0);

    printf ("Initializing the matrix\n");
    #pragma omp parallel num_threads(omp_get_num_procs())
    {
        #pragma omp for private(i)
        for (i = 0; i < (m*k); i++)
            A[i] = (double)(1);
        #pragma omp for private(i)
        for (i = 0; i < (k*n); i++)
            B[i] = (double)(1);
        #pragma omp for private(i)
        for (i = 0; i < (m*n); i++)
            C[i] = 0.0;
    }

    printf ("\nMatrix multiplication calculations using OpenMP and %d threads\n", omp_get_num_procs());
    t=omp_get_wtime();
    #pragma omp parallel for private(i,j,l) num_threads(omp_get_num_procs())
    for (i=0;i<m;i++)
        for (j=0;j<k;j++)
            for (l=0;l<n;l++)
                C[l+i*n] += A[j+i*k]*B[l+j*n];
    t=omp_get_wtime()-t;
    printf("Computation time (%d OpenMP threads) = %lf s\n\n",omp_get_num_procs(),t);

    print_matrix(m, k, A, 'A');
    print_matrix(k, n, B, 'B');
    print_matrix(m, n, C, 'C');

    #pragma omp parallel for private(i)
    for (i = 0; i < (m*n); i++)
        C[i] = 0.0;

    printf ("\nMatrix multiplication calculations using Cauchy formulas - 1 thread\n");
    t=omp_get_wtime();
    for (i=0;i<m;i++)
        for (j=0;j<k;j++)
            for (l=0;l<n;l++)
                C[l+i*n] += A[j+i*k]*B[l+j*n];
    t=omp_get_wtime()-t;
    printf("Computation time (1 thread) = %lf s\n\n",t);

    print_matrix(m, k, A, 'A');
    print_matrix(k, n, B, 'B');
    print_matrix(m, n, C, 'C');

    printf ("\nFreeing up memory\n");
    free(A);
    free(B);
    free(C);

    return 0;
}

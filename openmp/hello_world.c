#include <omp.h>
#include <stdio.h>

int main()
{
	int numt = omp_get_num_threads();
	// Here numt = 1
	printf("#Threads = %d\n", numt);
	#pragma omp parallel
	{
		/* 
		Number of threads can be specified from the command line 
		export OMP_NUM_THREADS=4	
		*/
		int tid = omp_get_thread_num();
		printf("Hello World from thread %d\n", tid);
		/*
		gcc -fopenmp filename.c
		is used to compile this code
		*/
		numt = omp_get_num_threads();

		// When declared here, the variables are private
		// When declared outside, the variables are shared
	}
	// Here numt = 4 (i.e. the numer specified from the terminal)
	printf("#Threads = %d\n", numt);
}

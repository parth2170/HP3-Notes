#include <omp.h>
#include <stdio.h>

#define SIZE 1000000

int main()
{
	// Declare array
	int i, tid, numt, arr[SIZE];
	for(int i = 0; i < SIZE; i ++)
	{
		arr[i] = 1;
	}
	
	// Serial code
	double t1 = omp_get_wtime();
	int sum = 0;
	for(i = 0; i < SIZE; i++)
	{
		sum += arr[i];
	}
	double t2 = omp_get_wtime();
	printf("Running Serially\nSum = %d\tTime taken = %g\n", sum, t2-t1);

	// Parallel code
	t1 = omp_get_wtime();
	sum = 0;
	#pragma omp parallel default(shared) private(i,tid)
	{
		int from, to, psum = 0;
		tid = omp_get_thread_num();
		numt = omp_get_num_threads();

		// First divide the array into equal parts for each thread
		from = (SIZE/numt) * tid;
		to = (tid == numt - 1) ? SIZE - 1 : (SIZE/numt) * (tid + 1) - 1;

		for(i = from; i <= to; i++)
		{
			// #pragma omp critical leads to huge increase in time
			// sum += arr[i];
			psum += arr[i];
		}
		#pragma omp critical
		sum += psum;
	}
	t2 = omp_get_wtime();
	printf("\nRunning Parallely without omp for\nSum = %d\tTime taken = %g\n", sum, t2-t1);

	// Parallel code with omp for
	t1 = omp_get_wtime();
	sum = 0;
	#pragma omp parallel default(shared)
	{
		int psum = 0;
		#pragma omp for
		for(i = 0; i < SIZE; i++)
		{
			psum += arr[i];
		}
		#pragma omp critical
		sum += psum;
	}
	t2 = omp_get_wtime();
	printf("\nRunning Parallely with omp for\nSum = %d\tTime taken = %g\n", sum, t2-t1);

	// Parallel code with reduction
	t1 = omp_get_wtime();
	sum = 0;
	#pragma omp parallel default(shared) reduction(+: sum)
	{
		#pragma omp for
		for(i = 0; i < SIZE; i++)
		{
			sum += arr[i];
		}
	}
	t2 = omp_get_wtime();
	printf("\nRunning Parallely with reduction\nSum = %d\tTime taken = %g\n", sum, t2-t1);
}


/*  Assignment 2 
	Block Wise reduction
	Author: Parth Tiwari
	Roll: 16IM30025
	Date: 26th Feb 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <cuda.h>
#include <cuda_runtime.h>

__global__ void reduce(float* A, float* B, int q)
{
 	
	int num_threads = blockDim.x;
	int block_num = blockIdx.y * gridDim.x + blockIdx.x;
	int tid = block_num * num_threads + threadIdx.x;

 	for(int stride = 1; stride < num_threads; stride *= 2)
 	{
 		__syncthreads();

 		if(tid % (2* stride) == 0)
 		{
 			A[tid] += A[tid + stride];
 		}
 	}

 	if(tid % q == 0)
 	{
 		B[block_num] = A[tid]/q;
 	}

}


int main()
{
	int T, p, q;

	scanf("%d", &T);

	while(T--)
	{
		scanf("%d %d", &p, &q);

		p = pow(2, p);
		q = pow(2, q);

		size_t size = p*sizeof(float);

		float *A;
		float *B;
		A = (float*)malloc(size);
		B = (float*)malloc(size/q);

		for(int i = 0; i < p; i++)
		{
			scanf("%f", &A[i]);
		}

		cudaError_t err = cudaSuccess;

		// Declare array for device
		float* A_d = NULL;
		float* B_d = NULL;

		err = cudaMalloc((void**)&A_d, size);
		err = cudaMalloc((void**)&B_d, size/q);

		//copy memory to device
	  	err = cudaMemcpy(A_d, A, size, cudaMemcpyHostToDevice);
  		err = cudaMemcpy(B_d, B, size/q, cudaMemcpyHostToDevice);


	  	int flag = 1;
	  	while(p >= q)
	  	{
			dim3 grid(ceil(sqrt(p/q)),ceil(sqrt(p/q)),1);
			dim3 block(q,1,1);

			if(flag == 1)
				reduce<<<grid,block>>>(A_d, B_d, q);
			else
				reduce<<<grid,block>>>(B_d, A_d, q);

			p /= q;
			size /= q;
			flag *= -1;
		}

		if(flag == -1)
		{
			err = cudaMemcpy(B, B_d, size, cudaMemcpyDeviceToHost);
			for(int i = 0; i < p; i++)
				printf("%.2f ", B[i]);
		}
		else
		{
			err = cudaMemcpy(A, A_d, size, cudaMemcpyDeviceToHost);
			for(int i = 0; i < p; i++)
				printf("%.2f ", A[i]);	
		}

		cudaFree(A_d);
		cudaFree(B_d);
		free(A);
		free(B);

		printf("\n");
	}
	return 0;
}
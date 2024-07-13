#include<stdio.h>
#include<stdlib.h>
__global__ void arradd(int* md, int* nd, int* pd, int size)
{
	int myid = blockIdx.x*blockDim.x + threadIdx.x;	
	pd[myid] = md[myid] + nd[myid];
}
int main()
{
	int size = 2000 * sizeof(int);
	int m[2000], n[2000], p[2000],*md, *nd,*pd;
	int i=0;
	for(i=0; i<2000; i++ )
	{
		m[i] = i;
		n[i] = i;
		p[i] = 0;
	}
	cudaMalloc(&md, size);
	cudaMemcpy(md, m, size, cudaMemcpyHostToDevice);
	cudaMalloc(&nd, size);
	cudaMemcpy(nd, n, size, cudaMemcpyHostToDevice);
	cudaMalloc(&pd, size);
	dim3   DimGrid(10, 1);     
	dim3   DimBlock(200, 1);   
	arradd<<< DimGrid,DimBlock >>>(md,nd,pd,size);
	cudaMemcpy(p, pd, size, cudaMemcpyDeviceToHost);
	cudaFree(md); 
	cudaFree(nd);
	cudaFree (pd);

	for(i=0; i<2000; i++ )
	{
		printf("\t%d",p[i]);
	}	

}

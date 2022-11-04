#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int *AllocateArray(int N)
{
	int *arr = (int *)malloc(sizeof(int) * N);
	for(int i = 0; i < N; i++){
		arr[i] = (rand() % (10 * N));
	}
	return arr;
}

void SortArray(int *A, int N){
	for(int i = 0; i < N; i++){
		int switcher = 1;
		for(int j = 1; j < N-1; j++){
			if(A[i] > A[i+1]){
				int temp = A[i];
				A[i] = A[i+1];
				A[i+1] = temp;
				switcher = 0;
			}
		}
		if(switcher){
			break;
		}
	}
}

void DeallocateArray(int *A){
	free(A);
}

int main()
{
//	int sizes[8] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000};

// For fun:
   int sizes[11] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000,
                     256000, 512000, 1024000 };
  

    for (int i = 0 ; i < 11 ; i++)
    {
	double alloc_time = 0., sort_time = 0., dealloc_time = 0.;
	struct timeval startTime1;
	gettimeofday(&startTime1, 0);
	int *arr = AllocateArray(sizes[i]);
	struct timeval endTime1;
	gettimeofday(&endTime1, 0);
	alloc_time = (double)(endTime1.tv_sec - startTime1.tv_sec) + ((double)(endTime1.tv_usec - startTime1.tv_usec) / 1000000.);
        	
	struct timeval startTime2;
	gettimeofday(&startTime2, 0);
	SortArray(arr, sizes[i]);
	struct timeval endTime2;
	gettimeofday(&endTime2, 0);
	sort_time = (double)(endTime2.tv_sec - startTime2.tv_sec) + ((double)(endTime2.tv_usec - startTime2.tv_usec) / 1000000.);
		
	struct timeval startTime3;
	gettimeofday(&startTime3, 0);
	DeallocateArray(arr);
	struct timeval endTime3;
	gettimeofday(&endTime3, 0);
	dealloc_time = (double)(endTime3.tv_sec - startTime3.tv_sec) + ((double)(endTime3.tv_usec - startTime3.tv_usec) / 1000000.);
        
	printf("\tTime for allocation is %g, time per element = %g\n", alloc_time, alloc_time/sizes[i]);
	printf("\tTime for sort_time is %g, time per element = %g\n", sort_time, sort_time/sizes[i]);
	printf("\tTime for deallocation is %g\n", dealloc_time);
    }
}

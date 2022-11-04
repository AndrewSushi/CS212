#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*
void merge_sort(int *arr, int min, int max);
void merge(int *arr, int *temp, int min, int max, int min2, int max2);
void copy(int *arr, int *temp, int min, int max);
*/

int *AllocateArray(int N)
{
    /* Allocate an array with N integers.
     * The value of each element of the array should be a
     * random number between 0 and 10N.
     * Hint: use the rand() function and a modulo operator.
     */
	int *arr = (int *)malloc(sizeof(int) * N);
	for(int i = 0; i < N; i++){
		arr[i] = (rand() % (10 * N));
	}
	return arr;
}

/*
void SortArray(int *arr, int min, int N){
	int mid = (min + N)/2;
	int temp[N + 1];
	
	if(min==N){ // Only one element - Base case
		return;
	}

	SortArray(arr, min, mid); // Split for first half
	SortArray(arr, mid+1, N); // Split for second half

	// Merge arr[min]-arr[mid] and arr[mid+1]-arr[max] to temp[min]-temp[max]
	merge(arr, temp, min, mid, mid+1, N);
	
	copy(arr, temp, min, N);

}

void merge(int *arr, int *temp, int min, int max, int min2, int max2){
	int i = min;
	int j = min2;
	int k = min;

	while((i<=max)&&(j<=max2)){
		if(arr[i] < arr[j]){
			temp[k++] = arr[i++];
		}else{
			temp[k++] = arr[j++];
		}
	}

	while(i<=max){ // Copy the rest of arr[min]-arr[max]
		temp[k++] = arr[i++];
	}

	while(j<=max2){ // Copy the rest of arr[min2]-arr[max2]
		temp[k++] = arr[j++];
	}

}

void copy(int *arr, int *temp, int min, int max){
	for(int i=min; i<=max; i++){
		arr[i] = temp[i];
	}
}
*/

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
	int sizes[8] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000};

// For fun:
//   int sizes[11] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000,
//                     256000, 512000, 1024000 };
  

    for (int i = 0 ; i < 8 ; i++)
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
		
		/* Call the three functions in a sequence. Also use
         * gettimeofday calls surrounding each function and set the 
         * corresponding variable (alloc_time, sort_time, dealloc_time).
         */

        printf("Timings for array of size %d\n", sizes[i]);
        printf("\tTime for allocation is %g, time per element = %g\n", alloc_time, alloc_time/sizes[i]);
        printf("\tTime for sort_time is %g, time per element = %g\n", sort_time, sort_time/sizes[i]);
        printf("\tTime for deallocation is %g\n", dealloc_time);
    }
}

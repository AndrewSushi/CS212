#include <stdio.h>

void print_data(int arr[], int n);
void merge_sort(int arr[], int min, int max);
void merge(int arr[], int temp[], int min, int max, int min2, int max2);
void copy(int arr[], int temp[], int min, int max);

int main()
{
    int A[100] = { 252, 657, 268, 402, 950, 66, 391, 285, 133, 577, 649, 166, 987, 314, 954, 214, 920, 230, 904, 801, 40, 552, 369, 682, 202, 712, 395, 517, 755, 603, 134, 385, 428, 941, 443, 477, 95, 647, 687, 737, 673, 19, 325, 697, 577, 181, 45, 964, 267, 600, 858, 145, 780, 760, 949, 508, 673, 717, 446, 634, 635, 679, 466, 474, 916, 855, 216, 899, 804, 159, 237, 625, 963, 388, 437, 682, 821, 325, 805, 876, 968, 414, 190, 434, 902, 794, 752, 729, 77, 243, 705, 953, 765, 637, 765, 158, 166, 599, 70, 927 };
	int n = (sizeof(A)/sizeof(A[0]));
	merge_sort(A, 0, n-1);
	print_data(A, n);

}

void merge_sort(int arr[], int min, int max){
	int mid = (min + max)/2;
	int temp[max + 1];
	
	if(min==max){ // Only one element - Base case
		return;
	}

	merge_sort(arr, min, mid); // Split for first half
	merge_sort(arr, mid+1, max); // Split for second half

	// Merge arr[min]-arr[mid] and arr[mid+1]-arr[max] to temp[min]-temp[max]
	merge(arr, temp, min, mid, mid+1, max);
	
	copy(arr, temp, min, max);

}

void merge(int arr[], int temp[], int min, int max, int min2, int max2){
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

void copy(int arr[], int temp[], int min, int max){
	for(int i=min; i<=max; i++){
		arr[i] = temp[i];
	}
}

void print_data(int arr[], int n){
	int i=0;
	while(i<n){
		printf("\t%d", arr[i]);
		i++;
		if(i%10 == 0){
			printf("\n");
		}
	}
}

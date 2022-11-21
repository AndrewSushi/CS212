/*
The main difference between array based dictionaries and hash table based dictionaries are that storing and fetching time are much different. 
For example, array based storing would be O(n) since it would take n (linear) time to store the next element since it has to search through the entire array for an empty slot. 
However hash tables are different in the sense that you have to do computations adn then recieve an index so in theory it will be O(1) time since the computations are not dependant on the length or the array. 
However, one thing to note is that using a hash function will take up more memory since you have functions that are stored within the memory. 
However, I have a theory, initially with smaller sizes, array based implementation will be faster since there are less instructions to do when storing and retriving. 
But as n, where n is the size of the array, approaches infinity, the time it takes for storing and fetching will slow down exponentially. 
For example, if the array size is 10, to store 10 elements in an array based implementation it will take 55 iterations since each element stores will take n iterations to store in the worst case scenerio. 
Hence the summation of 1-10 will be 55 iterations. If the time complexity of an array look up is constant, then we can say that there will be 55 instructions. 
However with a hash table implementation, if there are 10 elements, the worst case scenario, there will be 9 collisions. 
And with that there will be function calls and hashing to find the key. And since there is multiplication within loops, there would be multiple instructions done on each iteration which will add up to more than 55 instructions. 
After testing this theory with only 20 elements, the results are what follows:
Array Based: 		Avg 0.000027 seconds | with 10 runs
Hash Table Based:	Avg 0.000039 seconds | with 10 runs
The data above shows that with the smaller data set size, the hash table implementation perormed worse just as expected. 
However, when looking at the full data set of the DJIA, we can see this trend does not stay for long. 
With all the the full data for the DJIA, the results are what follows:
Array Based: 		Avg 0.288749 | with 10 runs
Hash Table Based: 	Avg 0.011048 | with 10 runs
The data above shows quite the contrary to the previous data when looking at a much bigger data size.
This is because although there are a lot more initial computations and instructions with the hsh function, as n approaches infinity, the number of instructions per iteration remains the same. 
However, with the array based implementation, using the same formula, the summation from 1 to n will be quite large compared to the hash table instructions.
However, hash table performance does change drastically based on the actual hash function.
For example, hash functions that are dependant on multiplication will run slower than those that depend on addition since there are more instructions that will have to be done.
Also another important thing to note is that hash functions should try to incorporate the least amount of collisions since if there is a computation there will be even more instructions done to try and recomputate a new index. For example, in the lecture slides for lecture15, we were presented with two different hash functions.
Hash1 implemented only addition, which hash2 implemented a mix of addition and multiplication. Even though hash2 would take more instructions since there is multiplication, it pays off since there is a lower chance for collision. Which will cause hash2 to be more efficient
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 20000

typedef struct{
	char *keys[MAX_SIZE];
	float values[MAX_SIZE];
} ArrayDictionary;

unsigned int hash1(char *key){
	unsigned long idx = 0;
	while(*key != '\0'){
		idx += *key;
		key++;
	}
	return idx % MAX_SIZE;
}

#define A 23L
long hash2(char *key){
	unsigned long sum = 1;
	while(*key != '\0'){
		sum = A * sum + (unsigned long)(*key);
		key++;
	}
	return (long)(sum % MAX_SIZE);
}

int compare(char *str1, char *str2){
	while(*str1 != '\0' || *str2 != '\0'){
		if(*str1 != *str2){
			return 0;
		}
		str1++;
		str2++;
	}
	return 1;
}

void Initialize(ArrayDictionary *ad){
	for(int i = 0; i < MAX_SIZE; i++){
		ad->keys[i] = "-1";
		ad->values[i] = -1.;
	}
}

void Store(ArrayDictionary *ad, char *key, float value){
	unsigned int idx = hash1(key);
	unsigned int idx2 = hash2(key);
	unsigned int poly = 0;
	int i = 1;
	if(compare(ad->keys[idx], "-1")){
		ad->keys[idx] = key;
		ad->values[idx] = value;
		return;
	}else if(compare(ad->keys[idx2], "-1")){
		ad->keys[idx2] = key;
		ad->values[idx2] = value;
		return;
	}else{
		while(i < MAX_SIZE){
			poly = (idx + (i * idx2)) % MAX_SIZE;
			if(compare(ad->keys[poly], "-1")){
				ad->keys[poly] = key;
				ad->values[poly] = value;
				return;
			}
			i++;
		}
	}
}

float Fetch(ArrayDictionary *ad, char *key){
	unsigned int idx = hash1(key);
	unsigned int idx2 = hash2(key);
	unsigned int poly = 0;
	int i = 1;
	if(compare(ad->keys[idx], key)){
		return ad->values[idx];
	}else if(compare(ad->keys[idx2], key)){
		return ad->values[idx2];
	}else{
		while(i < MAX_SIZE){
			poly = (idx + (i * idx2)) % MAX_SIZE;
			if(compare(ad->keys[poly], key)){
				return ad->values[poly];
			}
			i++;
		}
	}
	return 0.;
}

int main(){
	FILE *f = fopen("DJIA", "r");
	if(f == NULL){
		fprintf(stderr, "Unable to open file \"DJIA\" ... did you copy it to the current directory?\n");
		exit(EXIT_FAILURE);
	}

    ArrayDictionary ad;
    Initialize(&ad);
    
	size_t size = 1024;
    char *buffer = malloc(size*sizeof(char));
	clock_t start = clock();
    while(getline(&buffer, &size, f) > 0)
    {
		if(buffer[0] == 'D'){
			continue;
		}
		char str[8];
		float open, high, low, closePrice;

		sscanf(buffer, "%s %f %f %f %f", str, &open, &high, &low, &closePrice);
		char *str_dup = strdup(str);
		Store(&ad, str_dup, closePrice);
    }
	clock_t end = clock();
	double totalTime = ((double) (end - start)) / CLOCKS_PER_SEC;
	float sum = 0;
    char dates[91][10] = {
                 "02/19/21", "02/19/20", "12/19/19", "12/12/19", "12/02/19", "11/22/19", "11/12/19", "10/22/19", "10/02/19", 
                 "09/12/19", "08/22/19", "08/12/19", "08/02/19", "07/22/19", "07/12/19", "07/02/19", "06/12/19", "05/22/19", 
                 "05/02/19", "04/22/19", "04/12/19", "04/02/19", "03/22/19", "03/12/19", "02/22/19", "02/19/19", "02/12/19", 
                 "01/22/19", "01/02/19", "12/19/18", "12/19/17", "12/19/16", "02/19/16", "02/19/15", "12/19/14", "02/19/14", 
                 "12/19/13", "02/19/13", "12/19/12", "12/19/11", "02/19/10", "02/19/09", "12/19/08", "02/19/08", "12/19/07", 
                 "12/19/06", "12/19/05", "02/19/04", "12/19/03", "02/19/03", "12/19/02", "02/19/02", "12/19/01", "12/19/00", 
                 "02/19/99", "02/19/98", "12/19/97", "02/19/97", "12/19/96", "12/19/95", "12/19/94", "02/19/93", "02/19/92", 
                 "12/19/91", "02/19/91", "12/19/90", "12/19/89", "12/19/88", "02/19/88", "02/19/87", "12/19/86", "02/19/86", 
                 "12/19/85", "02/19/85", "12/19/84", "12/19/83", "02/19/82", "02/19/81", "12/19/80", "02/19/80", "12/19/79", 
                 "12/19/78", "12/19/77", "02/19/76", "12/19/75", "02/19/75", "12/19/74", "02/19/74", "12/19/73", "12/19/72", 
                 "02/19/71"
           };
	for (int i = 0 ; i < 91 ; i++)
    {
        float val = Fetch(&ad, dates[i]);
        if (val == 0.)
        {
            printf("Bad fetch!\n");
            exit(EXIT_FAILURE);
        }
		sum += val;
    }
    printf("Over the 91 days, the average value was %d\n", (int)(sum/91.0));
	printf("Time: %lf\n", totalTime);
    // Over the 91 days, the average value was 13209
}

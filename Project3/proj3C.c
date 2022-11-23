/* CS 212 Project: Donations (2022)
   ~Always appreciated, never expected, non-refundable~

   Author: S. Isaac Geronimo Anderson (Fall 2022)
   */

#include <stdio.h>   /* printf */
#include <stdlib.h>  /* malloc */
#include <string.h>  /* strcmp */

/* Do not change these values for your submission. */
#define QUEUE_SIZE 12  /* Note: Works with 12 on 3C-input.txt */
#define BLOOD_TYPES 4
#define LINE_LENGTH 80

int currentDonors = 0; // Since there are multiple blood types this keeps track of all
int currentRecips = 0;

char types[BLOOD_TYPES] = {'X', 'B', 'A', 'O'}; // X represents AB

struct queue
{
	int front;
	int back;
	char *strings[LINE_LENGTH];
	int population;
};
typedef struct queue Queue;

void initializeQueue(Queue *q){
	q->front = 0;
	q->back = 0;
}

void enqueue(char *str, Queue *q){
	q->strings[q->back] = strdup(str);
	q->back++;
	q->population++;
}

char *dequeue(Queue *q){
	char *dequeued = q->strings[q->front];
	q->front++;
	q->population--;
	return dequeued;
	
}
/* Here is a suggested helper function for checking blood type
   compatibility. */
int isDonorToRecipient(char donor, char recipient)
{
	if ((donor == 'O') || (donor == recipient))
		return 1;
	if ((donor == 'A') && (recipient == 'X'))
		return 1;
	if ((donor == 'B') && (recipient == 'X'))
		return 1;
	return 0;
}

int getBloodIndex(char bloodType){
	switch (bloodType){
		case 'X':
			return 0;
		case 'B':
			return 1;
		case 'A':
			return 2;
		case 'O':
			return 3;
	}
}

char getBloodType(char *person){
	person += 2; // skip the first two characters
	if(*person == 'O' || *person == 'B'){
		return *person;
	}else if(person[1] == ':'){
		return 'A';
	}else{
		return 'X'; // 'X' is blood type AB
	}
}

void printMatch(char *don, char *rec, char *sur){
	printf("MATCH: %s donates to %s via Dr. %s\n", don, rec, sur);
}

char *getName(char *person){
	int colonCounter = 0;
	int i = 0;
	char *name;
	if(person[0] != 'S'){
		while(colonCounter != 2){ // Renmove Colons
			if(*person == ':'){
				colonCounter++;
			}
			person++;
		}
	}else{
		while(colonCounter != 1){ // Renmove Colons
			if(*person == ':'){
				colonCounter++;
			}
			person++;
		}
	}
	char *temp = person;
	while(*person != '\n'){
		*person = *person;
		person++;
	}
	*person = '\0';
	person = temp;
	return person;
}

void printQueue(struct queue *q);

int isValidSurgery(char don, char rec){
	if(don == 'O' && don == rec){ // Both O
		return 1;
	}

}


//int findRecip(Queue **rec, char bloodType){ // Return the index of the recipient blood type that is matched}

/*
int findPriorityRec(Queue **rec, char bloodDonor){ // Returns the index corresponding to bloodType
	if(blood == 'X'){
		if(rec[0]->population){
			return 0; // There is an AB donor and Recip
		}else{
			return -1; // No AB rec
		}
	}else if(blood ==  'B'){
		if(rec[0]->population){
			if((rec[1]->population && rec[2]->population && rec[3]->population) == 0){
				return 0; // Only recip in all queues
			}
		}
		if(rec[1]->population){
			return 1; // There is a type B;
		}else{
			return -1;
		}
	}else if(blood == 'A'){	
		if(rec[0]->population){
			if((rec[1]->population && rec[2]->population && rec[3]->population) == 0){
				return 0;
			}
		}
		if(rec[2]->population){
			return 2; // There is a type A;
		}else{
			return -1;
		}
	}else{
		if(rec[0]->population){
			if((rec[1]->population && rec[2]->population && rec[3]->population) == 0){
				return 0;
			}
		}
		if(rec[3]->population){
			return 3; // There is a type A;
		}else{
			return -1;
		}
	}
//	for(int i = 0; i < 4; i++){
//		printQueue(don[i]);
//	}
}
*/
/*
int findPriorityDon(Queue **rec, char bloodRecip){ // Returns the index corresponding to bloodType
	if(blood == 'X'){
		if(rec[0]->population){
			return 0; // There is an AB donor and Recip
		}else{
			return -1; // No AB rec
		}
	}else if(blood ==  'B'){
		if(rec[0]->population){
			if((rec[1]->population && rec[2]->population && rec[3]->population) == 0){
				return 0; // Only recip in all queues
			}
		}
		if(rec[1]->population){
			return 1; // There is a type B;
		}else{
			return -1;
		}
	}else if(blood == 'A'){	
		if(rec[0]->population){
			if((rec[1]->population && rec[2]->population && rec[3]->population) == 0){
				return 0;
			}
		}
		if(rec[2]->population){
			return 2; // There is a type A;
		}else{
			return -1;
		}
	}else{
		if(rec[0]->population){
			if((rec[1]->population && rec[2]->population && rec[3]->population) == 0){
				return 0;
			}
		}
		if(rec[3]->population){
			return 3; // There is a type A;
		}else{
			return -1;
		}
	}
//	for(int i = 0; i < 4; i++){
//		printQueue(don[i]);
//	}
}

*/

int don_idx = 0;
int rec_idx = 0;
int findPrioritySurgery(Queue **don, Queue **rec, char bloodType, int isDonor){
	switch (bloodType){
		case 'X':
			if(isDonor){
				if(rec[0]->population != 0){
					printf("rec[0]: %d ANDREW\n", rec[0]->population);
					don_idx = 0;
					rec_idx = 0;
					return 0;
				}else{
					return -1;
				}
			}else{
				for(int i = 1; i < 4; i++){
					if(don[i]->population != 0){
						printf("don[%d]: %d\n", i, don[i]->population);
						rec_idx = 0;
						don_idx = i;
						return i;
					}
				}
				return -1;
			}
		case 'B':
			if(isDonor){
				if(rec[0]->population != 0){
					printf("rec[0]: %d ANDREW\n", rec[0]->population);
					don_idx = 1;
					rec_idx = 0;
					return 0;
				}else if(rec[1]->population != 0){
					printf("rec[1]: %d\n", rec[1]->population);
					don_idx = 1;
					rec_idx = 1;
					return 1;
				}else{
					return -1;
				}
			}else{
				if(don[1]->population != 0){
					printf("don[1]: %d\n", don[1]->population);
					don_idx = 1;
					rec_idx = 1;
					return 1;
				}else if(don[3]->population != 0){
					printf("don[3]: %d\n", don[3]->population);
					don_idx = 3;
					rec_idx = 1;
					return 3;
				}else{
					return -1;
				}
			}
		case 'A':
			if(isDonor){
				if(rec[0]->population != 0){
					printf("rec[0]: %d ANDREW\n", rec[0]->population);
					don_idx = 2;
					rec_idx = 0;
					return 0;
				}else if(rec[2]->population != 0){
					printf("rec[2]: %d\n", rec[2]->population);
					don_idx = 2;
					rec_idx = 2;
					return 2;
				}else{
					return -1;
				}
			}else{
				if(don[2]->population != 0){
					printf("don[2]: %d\n", don[2]->population);
					don_idx = 2;
					rec_idx = 2;
					return 2;
				}else if(don[3]->population != 0){
					printf("don[3]: %d\n", don[3]->population);
					don_idx = 3;
					rec_idx = 2;
					return 3;
				}else{
					return -1;
				}
			}
		case 'O':
			if(isDonor){
				for(int i = 0; i < 4; i++){
					if(rec[i]->population != 0){
						printf("rec[%d]: %d\n", i, rec[i]->population);
						don_idx = 3;
						rec_idx = i;
						return i;
					}
				}
				return -1;
			}else{
				if(don[3]->population != 0){
					printf("don[3]: %d\n", don[3]->population);
					don_idx = 3;
					rec_idx = 3;
					return 3;
				}else{
					return -1;
				}
			}
	}
}

int findPriority(Queue **don, Queue **rec, char bloodType, int isDonor){
	switch (bloodType){
		case 'X':
			if(isDonor){
				if(rec[0]->population != 0){
					return 0;
				}else{
					return -1;
				}
			}else{
				for(int i = 1; i < 4; i++){
					if(don[i]->population != 0){
						return i;
					}
				}
				return -1;
			}
		case 'B':
			if(isDonor){
				if(rec[0]->population != 0){
					return 0;
				}else if(rec[1]->population != 0){
					return 1;
				}else{
					return -1;
				}
			}else{
				if(don[1]->population != 0){
					return 1;
				}else if(don[3]->population != 0){
					return 3;
				}else{
					return -1;
				}
			}
		case 'A':
			if(isDonor){
				if(rec[0]->population != 0){
					return 0;
				}else if(rec[2]->population != 0){
					return 2;
				}else{
					return -1;
				}
			}else{
				if(don[2]->population != 0){
					return 2;
				}else if(don[3]->population != 0){
					return 3;
				}else{
					return -1;
				}
			}
		case 'O':
			if(isDonor){
				for(int i = 0; i < 4; i++){
					if(rec[i]->population != 0){
						return i;
					}
				}
				return -1;
			}else{
				if(don[3]->population != 0){
					return 3;
				}else{
					return -1;
				}
			}
	}
}

int isInQueue(Queue **q){
	for(int i = 0; i < 4; i++){
		if(q[i]->population){
			return 1;
		}
	}
	return 0;
}

void parseData(char *person, Queue **don, Queue **rec, Queue *sur){
	char *name = getName(person);
	if(person[0] == 'R'){
		char type = getBloodType(person);
		int idx = getBloodIndex(type);
		if(sur->population == 0){
			enqueue(name, rec[idx]);
		}else if(isInQueue(don)){
			int idx2 = findPriority(don, rec, type, 0);
			if(idx2 == -1){
				enqueue(name, rec[idx]);
			}else{
				printMatch(dequeue(don[idx]), name, dequeue(sur));
			}
		}else{
			enqueue(name, rec[idx]);
		}
	}else if(person[0] == 'D'){
		char type = getBloodType(person);
		int idx = getBloodIndex(type);
		if(sur->population == 0){
			enqueue(name, don[idx]);
		}else if(isInQueue(rec)){
			int idx2 = findPriority(don, rec, type, 1);
			if(idx2 == -1){
				enqueue(name, don[idx]);
			}else{
				printMatch(name, dequeue(rec[idx]), dequeue(sur));
			}
		}else{
			enqueue(name, don[idx]);
		}
	}else{
		if(isInQueue(rec) && isInQueue(don)){
			for(int i = 0; i < 2; i++){
				for(int j = 0; j < 4; j++){
					int idx = findPriority(don, rec, types[j], i);
					if(idx != -1){
						printf("%d %d\n", don_idx, rec_idx);
						printf("%d\n", don[don_idx]->population);
						printf("%d\n", rec[rec_idx]->population);
						printMatch(dequeue(don[don_idx]), dequeue(rec[rec_idx]), name);
						return;
					}
				}
			}
			enqueue(name, sur);
		}else{
//		int ifSurgery = 0;
//		for(int i = 0; i < 4; i++){
//			if(don[i]->population && rec[i]->population){
//				printMatch(dequeue(don[i]), dequeue(rec[i]), name);
//				printQueue(don[i]);
//				printQueue(rec[i]);
//				ifSurgery = 1;
//				break;
//			}
//		}
//		if(ifSurgery == 0){
			enqueue(name, sur);
//		}
		}
	}
}

void openFile(char *argv, Queue **don, Queue **rec, Queue *sur){
	FILE *f = fopen(argv, "r");
	if(f == NULL){
		printf("File not found in current path.\n");
		exit(EXIT_FAILURE);
	}
	char *linePtr = (char *)malloc(LINE_LENGTH);
	size_t n = LINE_LENGTH;
	ssize_t count = getline(&linePtr, &n, f);
	while(count != -1){
//		printf("%s\n", linePtr);
		parseData(linePtr, don, rec, sur);
		count = getline(&linePtr, &n, f);
	}
}

void printQueue(struct queue *q)
{
  printf("Printing queue %p\n", q);
  printf("\tThe index for the front of the queue is %d\n", q->front);
  printf("\tThe index for the back of the queue is %d\n", q->back);
  if (q->population == 0)
  {
    printf("\tThe queue is empty.\n");
  }
  else
  {
    for (int i = 0; i < q->population; i++)
    {
      int index = (q->front + i) % QUEUE_SIZE;
      printf("\t\tEntry[%d]: \"%s\"\n", index, q->strings[index]);
    }
  }
}

void prettyPrintQueue(struct queue *q, char *label, char *type)
{
  if (q->population == 0)
  {
    printf("No unmatched entries for %s (%s)\n", label, type);
  }
  else
  {
    printf("Unmatched %s (%s):\n", label, type);
    for (int i = 0; i < q->population; i++)
    {
      int index = (q->front + i) % QUEUE_SIZE;
      printf("%s\n", q->strings[index]);
    }
  }
}

int main(int argc, char **argv)
{
  /***  STEP #1: Implement your queue code and test it.  ***/

  /* This test code: */
 
/* 
	struct queue *q = malloc(sizeof (struct queue));
	initializeQueue(q);
	printQueue(q);
	enqueue("hello", q);
	printQueue(q);
	enqueue("world", q);
  	printQueue(q);
	printf("Dequeue: %s\n", dequeue(q));
	printQueue(q);
	free(q);
*/  


  /* Gives this output (with different pointers):

Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 0
	The queue is empty.
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 1
		Entry[0] = "hello"
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 2
		Entry[0] = "hello"
		Entry[1] = "world"
Dequeue: hello
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 1
	The index for the back of the queue is 2
		Entry[1] = "world"
  */

  /***
    STEP #2: Open the input file (argc/argv stuff).
             You should read the file line-by-line in the next step
             using fgets (or fscanf or getline).
             Note: You must not hard-code the input file name.
             You must not use fread.
             You should exit with an error if file opening fails.
  ***/
  /***
    STEP #3: After your queue code works and after you can read the
             file, implement the prompt.
             Note: Here is the print statement to use for a match:

  printf(
      "MATCH: %s donates to %s via Dr. %s\n",
      donor,
      recipient,
      surgeon);

    You will need four queues for recipients, and four queus for
    donors, so using arrays seems sensible. Suggested declarations
    for these arrays are included below this comment.

  ***/

  /* Here is a suggested helper array for facilitating matching as
    described in the prompt. The blood types are listed from most
    rare to least rare. */

	struct queue *donors[BLOOD_TYPES];
	struct queue *recipients[BLOOD_TYPES];
	struct queue *surgeons = malloc(sizeof *surgeons);
	initializeQueue(surgeons);

	for(int i = 0; i < 4; i++){
		donors[i] = (Queue *)malloc(sizeof(Queue));
		recipients[i] = (Queue *)malloc(sizeof(Queue));
		initializeQueue(donors[i]);
		initializeQueue(recipients[i]);	
	}
//	printf("%s\n", dequeue(surgeons));	
	openFile(argv[1], donors, recipients, surgeons);
//	printQueue(surgeons);
//	printQueue(donors[0]);
//	printQueue(recipients[0]);
//	printQueue(recipients[1]);
//	printQueue(recipients[2]);
//	printQueue(recipients[3]);

//	for(int i = 0; i < 4; i++){
//		printQueue(donors[i]);
//		printQueue(recipients[i]);
//	}
//	printQueue(surgeons);

//	findPriority(donors);

  /*
    STEP #4: After your matching code is done, add prettyPrintQueue
             calls for each of your recipient queues, your donor
             queues, and your surgeon queue. If you used the
             suggested "recipients" and "donors" arrays, and the
             "types" array, then you can use these print statements:
*/
//	for (int r = 0; r < BLOOD_TYPES; r++)
//		prettyPrintQueue(recipients[r], "recipients", types[r]);
//	for (int d = 0; d < BLOOD_TYPES; d++)
//		prettyPrintQueue(donors[d], "donors", types[d]);
//		prettyPrintQueue(surgeons, "surgeons", "type-agnostic");

/*
             If you did not use arrays for your recipient and donor
             queues, then you should print your recipient queues in
             this order, for example:


  prettyPrintQueue(recipients_AB, "recipients", "AB");
  prettyPrintQueue(recipients_A, "recipients", "B");
  prettyPrintQueue(recipients_B, "recipients", "A");
  prettyPrintQueue(recipients_O, "recipients", "O");

             Then, print your donor queues in the same order, then
             print your surgeon queue.
  */

  /* If you have time, be sure to free any memory you allocated. */
  free(surgeons);

  return EXIT_SUCCESS;
}


/* End. */

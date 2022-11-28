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

char types[BLOOD_TYPES] = {'X', 'B', 'A', 'O'}; // X represents AB

struct queue
{
	int front;
	int back;
	char strings[QUEUE_SIZE][LINE_LENGTH];
	int population;
};
typedef struct queue Queue;

void printQueue(struct queue *q);

void initializeQueue(Queue *q){
	q->front = 0;
	q->back = 0;
	q->population = 0;
}

void enqueue(char *str, Queue *q){
	if(q->back == QUEUE_SIZE - 1){
		strcpy(q->strings[q->back], str);
		q->back = 0;
	}else{
		strcpy(q->strings[q->back], str);
		q->back++;
	}
	q->population++;
}

char *dequeue(Queue *q){
	char *dequeued = q->strings[q->front];
	q->front++;
	q->population--;
	return dequeued;
	
}

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


int isInQueue(Queue **q){
	for(int i = 0; i < 4; i++){
		if(q[i]->population){
			return 1;
		}
	}
	return 0;
}

int testDon(Queue **don, Queue **rec, int donBlood, char *name, Queue *sur){
	for(int i = 0; i < 4; i++){
		if(isDonorToRecipient(types[donBlood], types[i])){
			if(rec[i]->population){
				printMatch(name, dequeue(rec[i]), dequeue(sur));
				return 1;
			}
		}
	}
	return 0;
}

int testRecip(Queue **don, Queue **rec, int recipBlood, char *name, Queue *sur){
	for(int i = 0; i < 4; i++){
		if(isDonorToRecipient(types[i], types[recipBlood])){
			if(don[i]->population){
				printMatch(dequeue(don[i]), name, dequeue(sur));
				return 1;
			}
		}
	}
	return 0;
}

int testSurgeon(Queue **don, Queue **rec, char *name){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(isDonorToRecipient(types[i], types[j])){
				if(don[i]->population && rec[j]->population){
					printMatch(dequeue(don[i]), dequeue(rec[j]), name);
					return 1;
				}
			}
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
			if(testRecip(don, rec, idx, name, sur) == 0){
				enqueue(name, rec[idx]);
			}
		}else{
			enqueue(name, rec[idx]);
		}
	return;
	}else if(person[0] == 'D'){
		char type = getBloodType(person);
		int idx = getBloodIndex(type);
		if(sur->population == 0){
			enqueue(name, don[idx]);
		}else if(isInQueue(rec)){
			if(testDon(don, rec, idx, name, sur) == 0){
				enqueue(name, don[idx]);
			}
		}else{
			enqueue(name, don[idx]);
		}
	return;
	}else{
		if(isInQueue(rec) && isInQueue(don)){
			if(testSurgeon(don, rec, name) == 0){
				enqueue(name, sur);
			}
		}else{
			enqueue(name, sur);
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
		parseData(linePtr, don, rec, sur);
		count = getline(&linePtr, &n, f);
	}
	free(linePtr);
	fclose(f);
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

	openFile(argv[1], donors, recipients, surgeons);

	char *types2[BLOOD_TYPES] = {"AB", "B", "A", "O"};
	for (int r = 0; r < BLOOD_TYPES; r++)
		prettyPrintQueue(recipients[r], "recipients", types2[r]);
	for (int d = 0; d < BLOOD_TYPES; d++)
		prettyPrintQueue(donors[d], "donors", types2[d]);
		prettyPrintQueue(surgeons, "surgeons", "type-agnostic");

  /* If you have time, be sure to free any memory you allocated. */
	for(int i = 0; i < 4; i++){
		free(recipients[i]);
		free(donors[i]);
	}
	free(surgeons);

	return EXIT_SUCCESS;
}


/* End. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_AMOUNT 10
#define LINE_SIZE 80

struct queue{
	int front;
	int back;
	int size;
	char **string;
};

void initQueue(struct queue *q){
	q->front = 0;
	q->back = 0;
	q->size = 0;
	q->string = (char **)malloc(STRING_AMOUNT);
	for(int i = 0; i < STRING_AMOUNT; i++){
		q->string[i] = (char *)malloc(LINE_SIZE);
	}
}

void enqueue(struct queue *q, char *str){
	strcpy(q->string[q->back], str);
	q->back++;
	q->size++;
}

char *dequeue(struct queue *q){
	char *temp = q->string[q->front];
	q->front++;
	q->size;
	return temp;
}

void printQueue(struct queue *q){
	for(int i = 0; i < STRING_AMOUNT; i++){
		printf("%s\n", q->string[i]);
	}
}

int main(){
	struct queue *q1 = (struct queue *)malloc(sizeof(struct queue));
	initQueue(q1);
	enqueue(q1, "Bunny");
	printf("%s\n", dequeue(q1));
	char *str1 = (char *)malloc(200);
	char str2[10];
	int ****************ptr1;
	printf("%d\n", sizeof(ptr1));
	printf("str1 %d byte(s)\n", sizeof(str1));
	printf("str2 %d byte(s)\n", sizeof(str2));
	printf("str1 %d byte(s)\n", sizeof(str1[23]));
	printf("str2 %d byte(s)\n", sizeof(str2[2]));
	return 0;
}

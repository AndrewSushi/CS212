#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 10
#define LINE_SIZE 80

struct stack{
	int top;
	char **string;
};

void initStack(struct stack *s){
	s->top = 0;
	s->string = (char **)malloc(sizeof(char *) * MAX_STACK);
	for(int i = 0; i < MAX_STACK; i++){
		s->string[i] = (char *)malloc(sizeof(char) * LINE_SIZE);
	}
}

void push(struct stack *s, char *str){
	strcpy(s->string[s->top], str);
	s->top++;
}

char *pop(struct stack *s){
	s->top--;
	char *temp = s->string[s->top];
	return temp;
}

void printStack(struct stack *s){
	int temp_top = s->top;
	while(temp_top != 0){
		temp_top--;
		printf("%s\n", s->string[temp_top]);
	}
}

int main(){
	struct stack *s = (struct stack *)malloc(sizeof(struct stack));
	initStack(s);
	push(s, "Bunny");
	push(s, "Pyon Pyon");
	push(s, "Kawaii");
	printStack(s);
	printStack(s);
	printf("%s\n", pop(s));
	printf("%s\n", pop(s));
}

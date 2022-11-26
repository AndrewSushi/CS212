#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 10
int top;

typedef enum
{
   ADD,
   MULT,
   SUBTRACT,
   UNSUPPORTED
} MathOperation;

void initStack(double *s){
	top = -1;
}

void push(double num, double *s){
	top++;
	s[top] = num;
}

double pop(double *s){
	double temp = s[top];
	top--;
	return temp;
}

double doMath(char *op, double *s){
	double v2 = pop(s); // Top
	double v1 = pop(s); // Second Top
	if(strcmp(op, "+") == 0){
		return v1 + v2;
	}else if(strcmp(op, "-") == 0){
		return v1 - v2;
	}else{
		return v1 * v2;
	}
}

void printStack(double *s){
	for(int i = 0; i < top; i++){
		printf("%d: %lf\n", i, s[i]);
	}
	printf("\n");
}

MathOperation GetOperation(char *op)
{
	if(op[1] != 0){ // If there is more than one operand
		return UNSUPPORTED;
	}
	if(*op == '+'){
		return ADD;
	}else if(*op == '-'){
		return SUBTRACT;
	}else if(*op == 'x'){
		return MULT;
	}else{
		return UNSUPPORTED;
	}
}

double StringToDouble(char *str)
{
	double sum;
	int switcher = 0;
	int deci_switcher = 0;
	int deci_mult = 10;
	int i = 0; 
	while(str[i] != '\0'){
		if(str[i] == '-'){
			switcher = 1;
			i++;
			continue;
		}
		if(str[i] == '.'){
			deci_switcher = 1;
			i++;
			continue;
		}
		if(deci_switcher == 1){
			double temp = (str[i] - 48);
			temp /= deci_mult;
			sum += temp;
			deci_mult *= 10;
		}else{
			sum *= 10;
			sum += (str[i] - 48);
		}
		i++;
	}
	if(switcher){
		sum *= -1;
	}
	return sum;
}

int main(int argc, char **argv){

	double *stack = (double *)malloc(sizeof(double) * STACK_SIZE);
	initStack(stack);

	for(int i = 1; i < argc; i++){
		MathOperation op = GetOperation(argv[i]);
		if(op != UNSUPPORTED){
			double temp = doMath(argv[i], stack);
			push(temp, stack);
		}else{
			double temp = StringToDouble(argv[i]);
			push(temp, stack);
		}
	}
	printf("The total is %lf\n", stack[0]);

    return 0;
}

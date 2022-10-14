#include <stdio.h>
#include <stdlib.h>

typedef enum
{
   ADD,
   MULT,
   SUBTRACT,
   DIV,
   UNSUPPORTED
} MathOperation;

void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}
void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
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
	}else if(*op == '/'){
		return DIV;
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
			if(switcher == 1 || (i != 0)){ // There is more than one '-' sign or not at the beginning
				IssueBadNumberError();
			}
			switcher = 1;
			i++;
			continue;
		}
		if(str[i] == '.'){
			if(deci_switcher == 1){ // There is more than one decimal in the number
				IssueBadNumberError();
			}
			deci_switcher = 1;
			i++;
			continue;
		}
		if(deci_switcher == 1){
			if((str[i] - 48) > 9 || (str[i] - 48) < 0){
				IssueBadNumberError();
			}
			double temp = (str[i] - 48);
			temp /= deci_mult;
			sum += temp;
			deci_mult *= 10;
		}else{
			if((str[i] - 48) > 9 || (str[i] - 48) < 0){
				IssueBadNumberError();
			}
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

int main(int argc, char *argv[])
{
    double v = StringToDouble(argv[1]);
    MathOperation op = GetOperation(argv[2]);
    double v2 = StringToDouble(argv[3]);
    double result = 0.;
    switch (op)
    {
		case ADD:
			result = v+v2;
         	break;
		case SUBTRACT:
			result = v-v2;
			break;
		case MULT:
			result = v*v2;
			break;
		case DIV:
			result = v/v2;
			break;
		case UNSUPPORTED:
			IssueBadOperationError();
			break;
	}
    printf("%d\n", (int) result);
 
    return 0;
}

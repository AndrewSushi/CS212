#include <stdio.h>
#include <stdlib.h>

int main(){
	char x;
	char *y;
	x = 'A';
	y = &x;
	printf("%c\n", x);
	printf("%c\n", *y);
	x = 'B';
	printf("%c\n", *y);
}

#include <stdio.h>

int main(int argc, char **argv){
	char c = argv[1][0];
	int counter;
	for(int i = 0; argv[2][i] != '\0'; i++){
		if(c == argv[2][i]){
		counter++;
		}
	}
	printf("'%c' occurs in '%s' %d times\n", c, argv[2], counter);
}

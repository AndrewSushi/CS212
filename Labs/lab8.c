#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	char *s = "x=3=3.14";
	char x;
	int y;
	float z;
	sscanf(s,"%c=%d=%f", &x, &y, &z);
	printf("%c=%d=%f\n", x, y, z);
	FILE *f = fopen(argv[1], "r");
	char *lineptr = (char *)malloc(10);
	size_t n = 10;
	ssize_t count = getline(&lineptr, &n, f);
	while(count != -1){
		printf("%s", lineptr);
		count = getline(&lineptr, &n, f);
	}
}

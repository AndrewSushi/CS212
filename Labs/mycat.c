#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	FILE *f = fopen(argv[1], 'r');
	char *buffer;
	if(f == NULL){
		printf("File not found in current path");
		exit(EXIT_FAILURE);
	}
	fseek(f, 0, SEEK_SET);
	int buff_size = ftell(f);
	fseek(f, 0, SEEK_SET);

	buffer = malloc(buff_size);
	fread(buffer, sizeof(char), buff_size, f);
	printf("%s\n", buffer);
	free(buffer);
	fclose(f);
}

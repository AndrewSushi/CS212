#include <stdio.h>
#include <stdlib.h>

int compare(char *ptr, char *word, int j){
	// Check the character before the start to makek sure it is isolated
	if(j != 0){
		if(!(*(ptr - 1) < 65 || ((*(ptr - 1) > 91) & *(ptr - 1) < 97) || *(ptr - 1) > 123)){
			return 0;
		}
	}
	int i = 0;
	while(word[i] != '\0'){
		if(ptr[i] != word[i]){
			return 0;
		}
		i++;
	}
	// Check the character after the end to make sure it is isolated
	if(!(ptr[i] < 65 || ((ptr[i] > 91) & ptr[i] < 97) || ptr[i] > 123)){
		return 0;
	}
	return 1;
}

int main(int argc, char **argv){
	FILE *f_in;
	int buff_size;
	char *buffer;
	int *counters = malloc(sizeof(int) * (argc-2));	

	f_in = fopen(argv[1], "r");
	
	if(f_in == NULL){
		printf("File not found in current path\n");
		exit(EXIT_FAILURE);
	}
	if(argc < 3){
		printf("Not enough arguments passed\n");
		exit(EXIT_FAILURE);
	}

	fseek(f_in, 0, SEEK_END);
	buff_size = ftell(f_in);
	fseek(f_in, 0, SEEK_SET);
	
	buffer = malloc(buff_size + 1);
	buffer[buff_size] = '\0';
	fread(buffer, sizeof(char), buff_size, f_in);
	char *temp_ptr = buffer;
	for(int c = 0; c < argc - 2; c++){
		int counter = 0;
		counters[c] = 0;
		buffer = temp_ptr;
		int i = 0;
		while(*buffer != '\0'){
			counters[c] += compare(buffer, argv[c+2], i);
			buffer = buffer + 1;
			i++;
		}
	}
	for(int i = 0; i < argc-2; i++){
		fprintf(stdout, "The word \"%s\" occurs %d times.\n", argv[i+2], counters[i]);
	}
	free(counters);
	buffer = temp_ptr;
	free(buffer);
	fclose(f_in);
}

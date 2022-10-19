#include <stdio.h>

int main(int argc, char **argv){
	for(int i = 0; i < argc; i++){
		printf("%s\n", argv[i]);
		for(int j = 0; argv[i][j] != '\0'; j++){
			printf("%c ", argv[i][j]);
		}
	}
}

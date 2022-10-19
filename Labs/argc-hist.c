#include <stdio.h>

int main(int argc, char **argv){
	for(int i = 0; i < argc; i++){
		int length;
		for(int j = 0; argv[i][j] != '\0'; j++){
			length = j;
		}
		printf("%s: %d\n", argv[i], ++length);
	}
}

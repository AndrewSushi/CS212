#include <stdio.h>

void odd_composites(int a, int b){
	for(int i = a; i<= b; i++){
		if(i % 2 == 0){
			continue;
		}
		for(int j = 2; j<=((i>>2)|5); j++){
			if(i % j == 0){
				printf("%d is a composite number.\n", i);
				break;
			}
		}
	}
}

int main(){
	odd_composites(10, 500);
}



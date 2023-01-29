#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_length(char *str){
	int count;
	for(count = 0; str[count] != '\0'; count++){}
	return count;
}

void *reverse(char *str){
	int len = str_length(str);
	char *temp = (char *)malloc(len);
	int i;
	for(i = 0; i < len; i++){
		temp[i] = str[len - i - 1];
	}
	temp[i] = '\0';
	char *ptr = str;
	while(*temp != '\0'){
		*str = *temp;
		str++;
		temp++;
	}
	str = ptr;
}

int main(){
	char *string = (char *)malloc(sizeof("Hello World!"));
	strcpy(string, "Hello World!");
	reverse(string);
	printf("%s\n", string);
}

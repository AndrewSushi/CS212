#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
	char *name;
	char *answer1;
	char *answer2;
	void (*favorite1)(char *);
	void (*favorite2)(char *);	
};

void favoriteFood(char *s){
	printf("My favorite food is %s\n", s);
}

void favoriteMovie(char *s){
	printf("My favorite movie is %s\n", s);
}

void favoriteSong(char *s){

	printf("My favorite song is %s\n", s);
}

void favoriteSport(char *s){
	printf("My favorite sport is %s\n", s);
}

void intro(struct person *p){
	printf("Hello my name is %s.\n", p->name);
	p->favorite1(p->answer1);
	p->favorite2(p->answer2);
}

int main(){
	struct person *Andrew = (struct person *)malloc(sizeof(struct person));
	Andrew->name = strdup("Andrew");
	Andrew->favorite1 = favoriteFood;
	Andrew->favorite2 = favoriteSong;
	Andrew->answer1 = strdup("Burgers");
	Andrew->answer2 = strdup("Ata - Rolling Pandemonium");
	intro(Andrew);
	free(Andrew->name);
	free(Andrew->answer1);
	free(Andrew->answer2);
	free(Andrew);
	return 0;
}

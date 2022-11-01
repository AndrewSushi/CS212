#include <stdio.h>
#include <stdlib.h>

struct cat{
	int age;
	char *name;
};

struct cat* CreateCat(char *name, int age){	
	struct cat *t = (struct cat *)malloc(sizeof(struct cat));
	t->age = age;
	t->name = name;
	return t;
}

int main(){
	struct cat *h = CreateCat("Hannah", 3);
	struct cat *k = CreateCat("Kat", 12);
	printf("%s is %d years old.\n", h->name, h->age);
	printf("%s is %d years old.\n", k->name, k->age);
	free(h);
	free(k);
	return 0;
}

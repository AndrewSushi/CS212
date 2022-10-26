#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv){

  //Type of error: Invalid read/write
  int i;
  int *a = malloc(sizeof(int) * 10);
  if (!a) return -1; /*malloc failed*/
  for (i = 0; i < 10; i++){
    a[i] = i;
  }
  free(a);

  
  //Type of error: 
  int *b;
  for (i=0; i < 10; i++){
    b = malloc(sizeof(int) * 100);
  }
  free(b);

  //Type of error: Uninit Variables
  int c[10];
  for (i = 0; i < 10; i++)
    c[i] = i;
    
  for (i = 0; i < 10; i++){
    printf("%d ", c[i]);
  }
  printf("\n");
  return 0;
}






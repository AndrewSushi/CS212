#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  /* Declare variables. */
  int i, n, f;
  f = 1;
  /* Return from main if we did not receive an argument. */
  if (argc < 2) return EXIT_FAILURE;

  /* Get the input argument. */
  n = atoi(argv[1]);

  /* Calculate the factorial. */
  for (i = 1; i <= n; i++)
    f = f * i;
  printf("Input: %d, factorial: %d\n", n, f);

  return EXIT_SUCCESS;
}

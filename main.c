#include <stdio.h>
#include <stdlib.h>

int division_method(int x, int m)
{
  return x % m;
}
void main()
{
  int const m = 7;
  int x = 25;
  int hash_value=0;
  /*Calling hash function */
  hash_value = division_method(x,m);
  printf("%d",hash_value);
}

/* functies als pointer example */
#include <stdio.h>

void func1(int *y)
{  
  *y = 3;
}

void func2(int *y)
{
  printf("func2) adres: %d, waarde: %d\n", y, *y);
}

int main()
{
  int x = 8;
  
  // declareer een pointer op een functie met een return value void
  // en die als argument een pointer op een int heeft.
  void (*f)(int *); 
  
  printf("main1) adres: %d, waarde: %d\n", &x, x);
  
  f = func1;
  f(&x);
  
  printf("main2) adres: %d, waarde: %d\n", &x, x);
  
  f = func2;
  f(&x);
  
  return 0;
}
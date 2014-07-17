#include <stdio.h>

int main() 
{
  char str[20];
  printf("What is your name? ");
  scanf("%s", &str);
  printf("Hi %-8s, glad to meet you\n", str);
  
  return(0);
}
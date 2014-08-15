/* ========================================================================== */
/*   voorbeeld.c                                                              */
/*                                                                            */
/* Aangepast door: Jeroen van Prooijen                                        */
/* stud.nr:        1595111                                                    */
/* Opleiding:      Security Technology (2013-2014)                            */
/* ========================================================================== */
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* printf */
#include <string.h> /* strcpy */

//////////////////////////////////////////////////////////////////////////////
// struct with linked neighbour
typedef struct huis
{
  char          inboedel[80];
  int           nr;
  struct huis   *next;
} HUIS, *PHUIS;

//////////////////////////////////////////////////////////////////////////////
// free all entry's of linkedlist
void free_mem(PHUIS phuis)
{
  PHUIS current;
  
  puts("\nfree-ing memory:");
  while(phuis)
  {
    current = phuis; 
    phuis = phuis->next;
    printf("  current= %9p, next= %9p\n", current, phuis);
    free(current);
  }
  
  puts("");
}

//////////////////////////////////////////////////////////////////////////////
// main() loop
int main(int argc, char *argv[])
{
  
  PHUIS phuis_een = (PHUIS)malloc(sizeof(HUIS));
  strcpy(phuis_een->inboedel, "dure inrichting");
  phuis_een->nr = 33;
  
  PHUIS phuis_twee = (PHUIS)malloc(sizeof(HUIS));
  strcpy(phuis_twee->inboedel, "ikea");
  phuis_twee->nr = 34;
  
  phuis_een->next = phuis_twee;
  
  PHUIS phuis = phuis_een;
  printf("dit huisnr         = %4d, address = %p\n", phuis->nr, phuis);
  printf("huisnr van buurman = %4d, address = %p\n", phuis->next->nr,
          phuis->next);
  
  free_mem(phuis);
  
  return 0;
}
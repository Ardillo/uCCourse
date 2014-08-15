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

#define DEBUG

///!//////////////////////////////////////////////////////////////////////////
/// struct with linked neighbour
typedef struct node
{
  char          name[80];
  int           nr;
  struct node   *next;
} NODE, *PNODE;

///!///////////////////////////////////////////////////////////////////////////
/// Global vars
PNODE top     = NULL;
int nodeCount = 0;

//////////////////////////////////////////////////////////////////////////////
// free all entry's of linkedlist
void free_nodes()
{
  #ifdef DEBUG
  puts("\nfree-ing memory:");
  #endif
  PNODE current;
  while(top)
  {
    current = top; 
    top = current->next;
    #ifdef DEBUG
    printf("  current= %9p, next= %9p\n", current, top);
    #endif
    free(current);
  }
  #ifdef DEBUG
  puts("");
  #endif
}

//////////////////////////////////////////////////////////////////////////////
// show all nodes in linkedlist
void show_nodes(PNODE node)
{  
  puts("\nPrint all nodes\n====================\n");
  PNODE current;
  while(node)
  {
    current = node; 
    node = current->next;
    puts(  " ===================");
    printf(" |%9p        |\n", current);
    puts(  " |-----------------|");
    printf(" |nr   = %9d |\n"
           " |naam = %9s |\n"
           " |next = %9p |\n", current->nr, current->name, current->next);
    puts(  " ===================");    
    puts(  "          |");
    puts(  "          V");
  }
  puts("========END=========");
}

//////////////////////////////////////////////////////////////////////////////
// main() loop
int main(int argc, char *argv[])
{
  PNODE een = (PNODE)malloc(sizeof(NODE));
  PNODE twee = (PNODE)malloc(sizeof(NODE));
  PNODE drie = (PNODE)malloc(sizeof(NODE));
  
  twee->next = een;
  drie->next = twee;
  top = drie;
  
  //printf("1: top test: %p\n", top);
  show_nodes(top);  
  //printf("2: top test: %p\n", top);
  
  free_nodes();
  
  
  return 0;
}
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

#define BUFFER_SIZE 80 /* een macht van 2 */
//#define DEBUG

///!//////////////////////////////////////////////////////////////////////////
/// struct with linked neighbour
typedef struct node
{
  char          name[BUFFER_SIZE];
  int           nr;
  struct node   *next;
} NODE, *PNODE;

///!///////////////////////////////////////////////////////////////////////////
/// Global vars
PNODE top     = NULL;
int nodeCount = 0;

//////////////////////////////////////////////////////////////////////////////
// print information about the program
void usage()
{
  puts("\n"
       "======================================================\n"
       "|                                                    |\n"
       "| SelfMadeLinkedList v1.0                            |\n"
       "|   author: Jeroen van Prooijen                      |\n"
       "|                                                    |\n"            
       "| Description:                                       |\n"
       "|   Program shows the usage of linked lists. A user  |\n"
       "|   can add, edit and delete nodes which are linked  |\n"
       "|   together automatically.                          |\n"
       "|   There's also an option to print the              |\n"
       "|   whole list on the screen.                        |\n"
       "|                                                    |\n"
       "======================================================\n");
}

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
// argument: pointer to node from where you want to start searching
void show_nodes(PNODE current)
{  
  puts("\n     Print nodes"
       "\n=====================\n");
  while(current)
  {
    puts(  "  ===================");
    printf("  |%9p        |\n", current);
    puts(  "  |-----------------|");
    printf("  |nr   = %9d |\n"
           "  |naam = %9s |\n"
           "  |next = %9p |\n", current->nr, current->name, current->next);
    puts(  "  ===================");    
    puts(  "           V");
    
    current = current->next;
  }
  puts(    "  ========NULL=======");
}

//////////////////////////////////////////////////////////////////////////////
// function: replaces the '\n' char with '\0' to avoid ugly printing
// argument: pointer to char
void formatString(char *name)
{
  int len = strlen(name);
  // replace len-1 char if == '\n' else return itself
  name[len-1] = (name[len-1] == '\n')? '\0' : name[len-1];
}

//////////////////////////////////////////////////////////////////////////////
// add new node to linkedlist
void add_node(void)
{
  int len;
  char number[BUFFER_SIZE];  
  PNODE newNode = (PNODE)malloc(sizeof(NODE));
  
  printf("Geef een naam voor de node  : ");
  fgets(newNode->name, BUFFER_SIZE, stdin);
  
  //printf("Geef een nummer voor de node: ");
  //fgets(number, BUFFER_SIZE, stdin);
  //newNode->nr = atoi(number);
  
  // format name 
  formatString(newNode->name);
  
  // format number
  newNode->nr = ++nodeCount;
  
  // format pointer 
  if(top!=NULL)
    newNode->next = top;
  
  // set global vars
  top = newNode;
}

//////////////////////////////////////////////////////////////////////////////
// check if there is at least 1 nodeCount
// returns; 1 if true, 0 if none
int nodes_exist()
{
  // if there are no nodes
  if(top == NULL)
  { 
    puts("there are no nodes!"); 
    return 0;
  }
  
  return 1;
}
 
//////////////////////////////////////////////////////////////////////////////
// deletes node from linkedlist,
// argument: pointer to top-node, locally called current
void del_node(PNODE current)
{
  if(!nodes_exist())
    return;
 
  char searchName[BUFFER_SIZE];
  
  printf("Welke node wil je verwijderen [naam]: ");
  fgets(searchName, BUFFER_SIZE, stdin);
  formatString(searchName);
  
  // if top-node is the to-be-deleted node
  if(strcmp(current->name, searchName) == 0)
  {
    top = current->next;
    free(current);
    return;
  } 
  
  // loop through the rest of the nodes and look one ahead
  for(current; current != NULL; current=current->next) 
    if(current->next && strcmp(current->next->name, searchName) == 0)
    {
      PNODE to_be_deleted = current->next;
      current->next = to_be_deleted->next;
      free(to_be_deleted);
    }
}
  
//////////////////////////////////////////////////////////////////////////////
// finds node and asks what to change
// argument: pointer to top-node, locally called current
void edit_node(PNODE current)
{
  if(!nodes_exist())
    return;
  
  char searchName[BUFFER_SIZE];
  
  printf("Welke node wil je veranderen [naam]: ");
  fgets(searchName, BUFFER_SIZE, stdin);
  formatString(searchName);
  
  for(current; current != NULL; current=current->next) 
    if(strcmp(current->name, searchName) == 0)
    {     
     char u[3], number[BUFFER_SIZE];
     
     puts("Wat moet er veranderd worden? n=name #=nr [n]");
     fgets(u, 3 ,stdin);
     
     switch((int)u[0])
     {
       case '#':         
         printf("Geef een nieuw nummer: ");
         fgets(number, BUFFER_SIZE, stdin);
         current->nr = atoi(number);
         return;
       default :
         printf("Geef een nieuwe naam: ");
         fgets(current->name, BUFFER_SIZE, stdin);
         formatString(current->name);
         return;
     }
    }
  
  puts("node not found, typo?");
  return;
}

void menu()
{
  char u[3];
  while(1)
  {
    puts("a=add d=del e=edit x=exit s=show_all ?=help [s]");
    
    // lelijke fix, linux heeft geen getch() ... werkt niet 
    // u != 13 --> 13 = ASCII enter
    //while((u=getchar())!='\n' && u != EOF && u != 13) 
    
    // nog veel lelijker, maar u[0] is de char waar het om gaat... zucht
    fgets(u, 3, stdin);
    
    #ifdef DEBUG
    int i;
    for(i=0; i<strlen(u); i++)
      printf("%i: %c\n", i, u[i]);
    #endif
      
      switch((int)u[0])
      {
        case 'a':
          add_node();
          break;
        case 'd':
          del_node(top);
          break;
        case 'e':
          edit_node(top);
          break;
        case 's':
          show_nodes(top);
          break;
        case 'x':
          free_nodes();
          puts("exiting ...");
          return;
        case '?':
          usage();
          break;
        default :
          show_nodes(top);
          break;
      }
  }
  return;
}
  

//////////////////////////////////////////////////////////////////////////////
// main() loop
int main(int argc, char *argv[])
{
  menu();
  return 0;
}
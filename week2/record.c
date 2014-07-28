/* ========================================================================== */
/*                                                                            */
/*      record.c                                                              */
/*      2014                                                                  */
/*                                                                            */
/* door:           Jeroen van Prooijen                                        */
/* stud.nr:        1595111                                                    */
/* Opleiding:      Security Technology (2013-2014)                            */
/*                                                                            */
/* Make a list of x records, where x is an asked number,                      */
/* Then fill these records one at a time                                      */
/* ========================================================================== */

#include <stdio.h> /* printf() */
#include <stdlib.h> /* exit(), EXIT_SUCCESS */
#include <string.h> /* strcpy() */

#define SIZE_BUFFER 10

#define DEBUG

///TODO&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// gebruik:        struct, malloc(), free(), gets(), atoi()
//                   &       &         &      X       &
// gebruik geen:   scanf()
//                   & 
///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// gets() geeft de mogelijkheid tot een overflow, daarom fgets() gebruikt als
// veiliger alternatief
///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

int aantal_records; // global var voor aantal entry's in lijst

typedef struct record
{
  int nr;
  char name[SIZE_BUFFER];
} RECORD, *PRECORD;
  
/////////////////////////////////////////////////////////////////////////////
// prints description if '?' as argument is given
int help(int *argc, char *arguments[])
{
  char *usage = 
  "\n=========================================================\n"
  "|\trecord v1.0, author Ardillo\t\t\t|\n"
  "|\t\t\t\t\t\t\t|\n"
  "|Make a list of x records, where x is an asked number\t|\n"
  "|Then fill these records one at a time \t\t\t|\n"
  "=========================================================\n";
  
  if(*argc > 1 && *arguments[1] == '?')
  {
    printf(usage);
    exit(EXIT_SUCCESS); // exit program
  }
  return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Ask for the amount of records the user want to fill in
void get_aantal_records()
{
  char cAmount[SIZE_BUFFER];
  
  printf("Geef het gewenste aantal records aan: ");
  fgets(cAmount, SIZE_BUFFER, stdin);
  aantal_records = atoi(cAmount);
  
  #ifdef DEBUG
  printf("amount=%i\n", aantal_records);
  #endif
}

/////////////////////////////////////////////////////////////////////////////
// Makes a one record, calculates the size of it and then 
PRECORD maak_recordlijst()
{
  RECORD temp;
  printf("Sizeof one record: %i\n", sizeof(temp));
 
  // pointer naar definitieve lijst met grote van temp * aantal_records
  PRECORD def_lijst = (PRECORD) malloc( (sizeof(temp) * aantal_records) );
  
  return def_lijst;
}

/////////////////////////////////////////////////////////////////////////////
// Fills the entire recordlist one by one
void fill_recordlijst(PRECORD lijst)
{
  int i;
  char input_buffer[SIZE_BUFFER];
   
  for(i=0; i<aantal_records; i++)
  {
    printf("Vullen van record %i van %i\n", (i+1), aantal_records);
    
    printf("nr:"); 
    fgets(input_buffer, SIZE_BUFFER, stdin);
    lijst[i].nr = atoi(input_buffer);
    
    printf("name:");
    fgets(input_buffer, SIZE_BUFFER, stdin);
    strcpy(lijst[i].name, input_buffer);
    
    printf("\n");
  }
  
}

/////////////////////////////////////////////////////////////////////////////
// Prints the recordlist on the screen
void print_recordlijst(PRECORD lijst)
{
  int i;
  PRECORD ps = lijst;
  puts("All records:");
  puts("============");
  for(i=0; i<aantal_records; ps++, i++)
    printf("[%i]\tnr:%4i\tnaam:%s", (i+1), ps->nr, ps->name);
}

/////////////////////////////////////////////////////////////////////////////
// main loop
int main(int argc, char *argv[])
{
  int i;
  PRECORD recordlijst;
 
  help(&argc, argv);
 
  get_aantal_records();
  
  recordlijst = maak_recordlijst();
  
  fill_recordlijst(recordlijst);
  
  print_recordlijst(recordlijst);
  
  free(recordlijst);
 
  return 0;
}
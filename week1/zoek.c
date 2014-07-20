/* ========================================================================== */
/*                                                                            */
/*      zoek.c                                                                */
/*      2014                                                                  */
/*                                                                            */
/* door:           Jeroen van Prooijen                                        */
/* stud.nr:        1595111                                                    */
/* Opleiding:      Security Technology (2013-2014)                            */
/*                                                                            */  
/* Search through a file for string:                                          */  
/*   ./zoek "string" file.txt                                                 */  
/* output will be:                                                            */  
/*   [line number][column number] line                                        */  
/* ========================================================================== */

#include <stdio.h>  /* printf, fopen, fclose, fgets */
#include <string.h> /* strlen, strcpy, strstr */

// (un)comment line below for debug output
#define DEBUG

#define MAXLINE 200 /* maximum chars in line */

int lineCount = 0;

///////////////////////////////////////////////////////////////////////////////
// reads a line from file and increments counter
// returns -1 if end of file is reached.
int readLine(char *line, int limit, FILE *file)
{
  if(fgets(line, limit, file) == NULL)
    return -1;
  else
    ++lineCount;
}

///////////////////////////////////////////////////////////////////////////////
// calculates column location in string
int calcColumn(char *pStartofString, char *pLocationWordFound)
{
  return ((pLocationWordFound - pStartofString) + 1);
}

///////////////////////////////////////////////////////////////////////////////
// searches for a substring in a string
// if found, calculate and return column location in string
int zoek(char *line, char zoekWoord[])
{
  char *phit;
  
  if((phit = strstr(line, zoekWoord)) != NULL)    
    return calcColumn(line, phit);
  
  return -1;
}

///////////////////////////////////////////////////////////////////////////////
// prints formatted line, with ANSI escape characters for colored printing
// output: 
//   [line][column] string
void printLine(int line, int column, char *string)
{
  printf("\033[32m[%3i][%3i] %s\033[0m", line, column, string);
}

/////////////////////////////////////////////////////////////////////////////
// main loop
int main(int argc, char *argv[])
{
  //////////////////
  // print help if not enough arguments are given
  char *usage = 
  "\n=========================================\n"
  "|\tzoek v1.0, author Ardillo\t|\n"
  "|\t\t\t\t\t|\n"
  "|usage: zoek <zoekstring> <bestandsnaam>|\n"
  "|eg:    zoek \"depeche mode\" bands.txt\t|\n"
  "=========================================\n";

  if (argc != 3) //indien geen of niet juiste aantal argumenten
  {
    printf(usage); //print help tekst
    return 1;
  }//////////////////
  
  //////////////////
  // check if file exists
  #ifdef DEBUG
    printf("DEBUG: arg-count=%d\n", argc);
    int i, size;
    for (i=0; i<argc; i++)
    {
      size = strlen(argv[i]);
      printf("[%d] %15s length=%i\n", i, argv[i], size);
    }
  #endif
  //////////////////
  
  ///////////////////
  // Open File
  FILE *fp;
  fp = fopen(argv[2], "r");
 
  if (fp == NULL) // check of file geopend is.
  {
    printf("File not opened!\n");
    return 1;
  }//////////////////
  
  //////////////////
  // Read every line in file and search for the word
  int column;
  char *zoekWoord = argv[1];
  char lineBuffer[MAXLINE];
  
  while(readLine(lineBuffer, MAXLINE, fp) != -1)
  {
    #ifdef DEBUG
    printf("[%3i] %s", lineCount, lineBuffer);
    #endif
    
    if( (column = zoek(lineBuffer, zoekWoord)) != -1)
      printLine(lineCount, column, lineBuffer);
  }//////////////////

  //////////////////
  // close file handler and program
  fclose(fp);
  return 1;
  //////////////////
}
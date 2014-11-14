// Ardillo
// small program to translate text into USB HID codes


#include <stdio.h>
#include <string.h>

#include "smallTranslator.h"

// (un)comment line below for debug output
//#define DEBUG

#define MAXLINE 200 /* maximum chars in line */

int lineCount;
///////////////////////////////////////////////////////////////////////////////
// Prints some help information
int help(int *argCount, char *argument[])
{
  char *usage = 
  "\n=================================================\n"
  "|\ttranslator v1.0, author Ardillo\t\t|\n"
  "|\t\t\t\t\t\t|\n"
  "|Prints text into the USB HID keyboard format\t|\n"
  "|Just pass a file as an argument, and copy\t|\n"
  "|paste the result in the program\t\t|\n"
  "=================================================\n";
  
  if ( *argCount > 1 && *argument[1] == '?') //indien geen of niet juiste aantal argumenten
  {
    printf(usage); //print help tekst
    return 1;
  }
  return 0;  
}

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
// Open File
FILE* openFile(char *fileName, char *mode)
{
  FILE *fp;
  fp = fopen(fileName, mode);
 
  if (fp == NULL) // check if file is opened
  {
    printf("File not opened!\n");
    return;
  }
  
  return fp;
}

///////////////////////////////////////////////////////////////////////////////
// Search through a line
int zoek(char *line)
{
  int i;
   
  #ifdef DEBUG
  printf("%s => ", line);
  #endif
  
  for(i=0; i< strlen(line); i++)
  {
    #ifdef DEBUG
    printf("char: %c, value:%i ", line[i], line[i]);
    #endif
    printf("%i, 0, ", lookup(line[i]));
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  FILE *fp = 0;
  char lineBuffer[MAXLINE] = "";
  
  if( help(&argc, argv))
    return 0;
  
  fp = openFile(argv[1], "r");
  
  while(readLine(lineBuffer, MAXLINE, fp) != -1)
  {
    //lineBuffer[strlen(lineBuffer) - 1] = '\0'; // strip trailing newline
    zoek(lineBuffer);
  }
  
}
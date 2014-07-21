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
#define NAMESIZE 30 /* maximum name size of searchString and fileName */

int lineCount = 0;

/////////////////////////////////////////////////////////////////////////////
// prints description if '?' as argument is given
int help(int *argCount, char *argument[])
{
  //////////////////
  // print arguments
  #ifdef DEBUG
    printf("DEBUG: arg-count=%d\n", *argCount);
    int i, size;
    for (i=0; i < *argCount; i++)
    {
      size = strlen(argument[i]);      
      printf("[%d] %15s length=%i\n", i, argument[i], size);     
    }
  #endif
  //////////////////
  
  char *usage = 
  "\n=========================================\n"
  "|\tzoek v1.0, author Ardillo\t|\n"
  "|\t\t\t\t\t|\n"
  "|searches for strings in a file\t\t|\n"
  "=========================================\n";
  
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
// calculates column location in string
int calcColumn(char *pStartofString, char *pLocationWordFound)
{
  return ((pLocationWordFound - pStartofString) + 1);
}

///////////////////////////////////////////////////////////////////////////////
// prints formatted line, with ANSI escape characters for colored printing
// output: 
//   [line][column] string
void printLine(int lineNumber, int column, char *string)
{
  printf("\033[32m[%3i][%3i] %s\033[0m", lineNumber, column, string);
}

///////////////////////////////////////////////////////////////////////////////
// writes formatted line to file, 
// with ANSI escape characters for colored printing
// output: 
//   [line][column] string
void writeLine2File(FILE *output2File, int lineNumber, int column, char *string)
{
  fprintf(output2File, "[%3i][%3i] %s", lineNumber, column, string);
}

///////////////////////////////////////////////////////////////////////////////
// searches for a substring in a string
// if found, calculate the column location in string, print the line. and 
// replace the found chars with '_' to find an possible second word in the 
// same line.
int zoek(char *line, char *zoekWoord, int *output2File, FILE *output)
{
  char *phit, zoekBuffer[strlen(line)];
  int column;
  
  strncpy(zoekBuffer, line, sizeof(zoekBuffer) ); // maak copy van line in buffer

  while((phit = strstr(zoekBuffer, zoekWoord)) != NULL)
  {
    column = calcColumn(zoekBuffer, phit);
    if(*output2File)
      writeLine2File(output, lineCount, column, line);
    
    printLine(lineCount, column, line);    
    memset(phit, '_', 1); // vervang 1e char door '_' in buffer
  }
  
  return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Open File
FILE* openFile(char *fileName, char *mode)
{
  FILE *fp;
  fp = fopen(fileName, mode);
  //fp = fopen("words.txt", "r");
 
  if (fp == NULL) // check if file is opened
  {
    printf("File not opened!\n");
    return;
  }//////////////////
  
  return fp;
}

///////////////////////////////////////////////////////////////////////////////
// clears unwanted '\n' chars in a string and replace them with '\0'
void clearNewLine(char *string)
{
  int i;
  for(i=0; i< strlen(string); i++)
  {
    //printf("%i) %c\n", i, string[i]);
    if(string[i] == '\n')
      memset(&string[i], '\0',1);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Ask for a searchString
void askSearchString(char *searchString)
{
  printf("Enter searchstring: ");
  fgets(searchString, NAMESIZE, stdin);
  clearNewLine(searchString);
  
  #ifdef DEBUG
  printf("zoekWoord: %s\n", searchString);
  #endif
}

///////////////////////////////////////////////////////////////////////////////
// Ask for a fileName
int askFileName(char *fileName)
{
  int i;
  char buffer[NAMESIZE];
  
  printf("Enter filename [press enter to continue in same file, "
         "press * to exit: ");
  fgets(buffer, sizeof(buffer), stdin);
  
  /// laten staan ivm documentatie
  //fgets(buffer, sizeof(buffer), stdin); /// leest '\n' aan eind mee in => ongewenst
  //scanf("%29s", buffer); /// accepteert geen '\n' als enige inhoud
  //while( (i = read(stdin, buffer, sizeof(buffer))) > 0); /// geef ook ongewenst gedrag
 
  // '\n' probleem opgelost met aparte functie
  clearNewLine(buffer);
  
  #ifdef DEBUG
  printf("OLD filename: \"%s\"\n", fileName);
  printf("BUFFER filename: \"%s\"\n", buffer);
  #endif
  
  switch(buffer[0])
  {
    case '\0':
      if (fileName[0] == 0)
        return 1;
      return 0;
    case '*': 
      return 1;
    default:
      strcpy(fileName, buffer);
      return 0;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Ask if output needs to be written to result.txt
int askOutput2File()
{
  char answer[NAMESIZE];
  
  printf("Do you want the output put in ""result.txt"" (y/n) [n]?");
  fgets(answer, NAMESIZE, stdin);
  
  switch(answer[0])
  {
    case 'y': return 1;
    default : return 0;
  }
}

/////////////////////////////////////////////////////////////////////////////
// main loop
int main(int argc, char *argv[])
{
  int column, finished = 0, output2File;
  char lineBuffer[MAXLINE], zoekWoord[NAMESIZE], bestandsNaam[NAMESIZE] = "";
  FILE *fp = 0, *output = 0;
  lineCount = 0;
  
  if( help(&argc, argv)) // prints help if '?' is given as argument
    return 0;
 
  output2File = askOutput2File();
  
  if(output2File)
    output = openFile("result.txt", "w");
  
  while(!finished)
  {    
    askSearchString(zoekWoord); // ask for searchString

    if(zoekWoord[0] == '\0') // searchString is empty
    {
      printf("invalid searchString, retry\n");
      continue;
    }

    if(askFileName(bestandsNaam))  
    {
      finished = 1;      
      break;
    }
    
    fp = openFile(bestandsNaam, "r");
     
    while(readLine(lineBuffer, MAXLINE, fp) != -1)
    {
      #ifdef DEBUG
      printf("[%3i] %s", lineCount, lineBuffer);
      #endif
      zoek(lineBuffer, zoekWoord, &output2File, output); 
    }
  }
  
  if(fp != 0)
    fclose(fp);
  
  if(output != 0)
    fclose(output);
  
  return 0;
}
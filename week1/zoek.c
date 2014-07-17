/* ========================================================================== */
/*                                                                            */
/*      zoek.c                                                                */
/*      2014                                                                  */
/*                                                                            */
/* door:           Jeroen van Prooijen                                        */
/* stud.nr:        1595111                                                    */
/* Opleiding:      Security Technology (2013-2014)                            */
/* ========================================================================== */

#include <stdio.h> //printf, fopen, fclose
//TODO nog te gebruiken (programma eis)
#include <string.h> 

//TODO programma eis
#define DEBUG

int main(int argc, char *argv[])
{
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
  }
  
  #ifdef DEBUG
    printf("DEBUG: arg-count=%d\n", argc);
    int i, size;
    for (i=0; i<argc; i++)
    {
      size = strlen(argv[i]);
      printf("[%d] %s length=%i\n", i, argv[i], size);
    }
  #endif
  
  char zoekString[strlen(argv[1])]; 
  strcpy(zoekString, argv[1]);
  
  char zoekBuffer[200];
  
  FILE *fp;
  fp = fopen(argv[2], "r");
 
  if (fp == NULL) // check of file geopend is.
  {
    printf("File not opened!\n");
    return 1;
  }
  
  // readline and return line included '\n' character
  while ( fgets(zoekBuffer, 200, fp) != NULL)
  {
    printf(zoekBuffer);
  }
  
  fclose(fp);
  return 1;
}
/* ========================================================================== */
/*                                                                            */
/*      GameOfLife.c                                                          */
/*      2014                                                                  */
/*                                                                            */
/* door:           Jeroen van Prooijen                                        */
/* stud.nr:        1595111                                                    */
/* Opleiding:      Security Technology (2013-2014)                            */
/*                                                                            */
/* Conway's Game of Life in C terminal program                                */
/* look playable examples on conwayslife.com                                  */
/* I only made a simple Glider example and Gosper Glider Gun                  */
/*                                                                            */
/*      * Just keep <enter> pressed during program to see an animation *      */
/*                                                                            */
/* ========================================================================== */
#include <stdio.h>  /* printf()              */
#include <stdlib.h> /* exit(), EXIT_SUCCESS  */
#include <string.h> /* memset() memmove()    */

#define WIDTH  50 /* const width of matrix   */
#define HEIGHT 30 /* const height of matrix  */

#define DEAD  '-'
#define ALIVE '#'

char matrix[(HEIGHT+2)][(WIDTH+2)];
char tempBuf[(HEIGHT+2)][(WIDTH+2)];

/////////////////////////////////////////////////////////////////////////////
// prints description if '?' as argument is given
int help(int *argc, char *arguments[])
{
  char *usage =
  "\n=========================================================\n"
  "|\tGame of Life, author Ardillo\t\t\t|\n"
  "|\t\t\t\t\t\t\t|\n"
  "|https://en.wikipedia.org/wiki/Conway's_Game_of_Life \t|\n"
  "|http://conwayslife.com/  (with a playable version)  \t|\n"
  "=========================================================\n";
 
  if(*argc > 1 && *arguments[1] == '?')
  {
    printf(usage);
    exit(EXIT_SUCCESS);
  }
  return 0;
}

/////////////////////////////////////////////////////////////////////////////
// fills matrix spaces with a character
void fill_matrix_with_zeros(char (*mat)[WIDTH+2])
{
  int i,j;
  
  for(i=0; i<(HEIGHT+2); mat++, i++)    
    for(j=0; j<(WIDTH+2); j++)
      (*mat)[j] = DEAD;
}

/////////////////////////////////////////////////////////////////////////////
// fills the border of the matrix with a character (padding)
void fill_padding(char (*mat)[WIDTH+2])
{
  int i, j;
  
  for(i=0; i<(HEIGHT+2); mat++, i++)     
  {
    for(j=0; j<(WIDTH+2); j++)
    {
      if(i == 0 || i == (HEIGHT+1))
        (*mat)[j] = '=';
      else if(j == 0 || j == (WIDTH+1))
        (*mat)[j] = '|';
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// draws the matrix on the screen inlcuding the padding
void draw_matrix_with_padding()
{
  int i, j;
  
  for(i=0; i<(HEIGHT+2); i++)     
  {
    for(j=0; j<(WIDTH+2); j++)
    {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  
  printf("\n");
}

/////////////////////////////////////////////////////////////////////////////
// draws the matrix on the screen without padding
void draw_matrix_without_padding()
{
  int i, j;
  
  for(i=1; i<(HEIGHT+1); i++)     
  {
    for(j=1; j<(WIDTH+1); j++)
    {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  
  printf("\n");
}

/////////////////////////////////////////////////////////////////////////////
// calculates the nest iteration and overwrite the original with the result
void calculate_next_matrix()
{
  int i, j, neighbours;

  fill_matrix_with_zeros(tempBuf);
  fill_padding(tempBuf);
  
  for(i=1; i<(HEIGHT+1); i++)
  {
    for(j=1; j<(WIDTH+1); j++)
    {
      neighbours = 0;
      char current = matrix[i][j];
      
      // check all 8 surrounding neighbours
      if(matrix[i-1][j-1] == ALIVE)
        neighbours++;
      if(matrix[i-1][j] == ALIVE)
        neighbours++;
      if(matrix[i-1][j+1] == ALIVE)
        neighbours++;
      if(matrix[i][j-1] == ALIVE)
        neighbours++;
      if(matrix[i][j+1] == ALIVE)
        neighbours++;
      if(matrix[i+1][j-1] == ALIVE)
        neighbours++;
      if(matrix[i+1][j] == ALIVE)
        neighbours++;
      if(matrix[i+1][j+1] == ALIVE)
        neighbours++;
      
      /// check count of neighbours
      // alive then die -> under-population
      if(current == ALIVE && neighbours < 2) 
        tempBuf[i][j] = DEAD;
      // stay alive
      if(current == ALIVE && neighbours == 2 || neighbours == 3) 
        tempBuf[i][j] = ALIVE; 
      // alive then die -> overcrowding
      if(current == ALIVE && neighbours > 3) 
        tempBuf[i][j] = DEAD;
      // dead then live -> reproduction
      if(current == DEAD && neighbours == 3) 
        tempBuf[i][j] = ALIVE;
      
    }
  }
  
  memmove(matrix, tempBuf, sizeof(matrix));
}

/////////////////////////////////////////////////////////////////////////////
// asks for user input
int ask_next_command(int *counter)
{
  char buffer[2];
  
  printf("Iteration: %i, Calculate next iteration? (y/n) [y]\n", *counter);
  fgets(buffer, sizeof(buffer), stdin);
  
  switch(buffer[0])
  {
    case 'n':
      return 0;
    default:
      return 1;
  }
}

/////////////////////////////////////////////////////////////////////////////
// Uses other drawing methods
void draw_matrix()
{
  draw_matrix_with_padding();
  //draw_matrix_without_padding();
}

/////////////////////////////////////////////////////////////////////////////
// clears the screen using ANSI escape sequences
// https://en.wikipedia.org/wiki/ANSI_escape_code
void clear_screen()
{
  printf("\033[2J\033[H");
}

/////////////////////////////////////////////////////////////////////////////
// function to draw the starting grid
void put_starting_data_in_matrix()
{
  /// Glider
  // # - -
  // - # #
  // # # -
  
  /*
  matrix[1][1] = ALIVE; 
  matrix[2][2] = ALIVE; 
  matrix[2][3] = ALIVE; 
  matrix[3][1] = ALIVE;
  matrix[3][2] = ALIVE;
  */
  
  /// Gosper Glider Gun
  // https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
  // data below is generated with some help of: http://conwayslife.com/
  matrix[2][26]  = ALIVE;
  matrix[3][24] = ALIVE;
  matrix[3][26] = ALIVE;
  matrix[4][14] = ALIVE;
  matrix[4][15] = ALIVE;
  matrix[4][22] = ALIVE;
  matrix[4][23] = ALIVE;
  matrix[4][36] = ALIVE;
  matrix[4][37] = ALIVE;
  matrix[5][13] = ALIVE;
  matrix[5][17] = ALIVE;
  matrix[5][22] = ALIVE;
  matrix[5][23] = ALIVE;
  matrix[5][36] = ALIVE;
  matrix[5][37] = ALIVE;
  matrix[6][2]  = ALIVE;
  matrix[6][3]  = ALIVE;
  matrix[6][12] = ALIVE;
  matrix[6][18] = ALIVE;
  matrix[6][22] = ALIVE;
  matrix[6][23] = ALIVE;
  matrix[7][2]  = ALIVE;
  matrix[7][3]  = ALIVE;
  matrix[7][12] = ALIVE;
  matrix[7][16] = ALIVE;
  matrix[7][18] = ALIVE;
  matrix[7][19] = ALIVE;
  matrix[7][24] = ALIVE; 
  matrix[7][26] = ALIVE;
  matrix[8][12] = ALIVE;
  matrix[8][18] = ALIVE;
  matrix[8][26] = ALIVE;
  matrix[9][13] = ALIVE;
  matrix[9][17] = ALIVE;
  matrix[10][14] = ALIVE;
  matrix[10][15] = ALIVE;
 
}

/////////////////////////////////////////////////////////////////////////////
// main loop
int main(int argc, char *argv[])
{
  int counter = 0;
  
  help(&argc, argv);
  
  // initialize
  fill_matrix_with_zeros(matrix);
  fill_padding(matrix);
  put_starting_data_in_matrix();
  clear_screen();
  draw_matrix();
 
  // while user wants next matrix
  while(ask_next_command(&counter))
  {
    calculate_next_matrix();
    clear_screen();
    draw_matrix();
    counter++;
  }
 
  printf("Exiting...\n\n");
  return 0;
}
/* ========================================================================== */
/*                                                                            */
/*   calcul.c                                                                 */
/*   (c) 2009 Michiel                                                         */
/*                                                                            */
/*   Usage of argc and argv[][]                                               */
/*   (argument counter and argument vector)                                   */
/*   note: run this program from the command prompt (cmd.exe)                 */
/* ========================================================================== */
/*                                                                            */
/* Aangepast door: Jeroen van Prooijen                                        */
/* stud.nr:        1595111                                                    */
/* Opleiding:      Security Technology (2013-2014)                            */
/* ========================================================================== */
#include <stdlib.h> // atoi
#include <stdio.h> // printf

#define DEBUG 

///////////////////////////////////////////////////////////////////////////////
// functie om machten uit te rekenen
float mverhef(float *waarde, float *macht)
{    
  // tot de macht 0 is altijd 1
  if (*macht == 0) return 1; 

  int i;
  float mresult = *waarde;
  
  // loop om de machten af te werken
  for (i = *macht; i > 1; i--)
    mresult *= *waarde;
  
  return mresult;
}

///////////////////////////////////////////////////////////////////////////////
// '+' operator
float plus(float *one, float *two){ return (*one + *two); }

///////////////////////////////////////////////////////////////////////////////
// '-' operator
float minus(float *one, float *two){ return (*one - *two); }

///////////////////////////////////////////////////////////////////////////////
// '*' operator
float multiply(float *one, float *two){ return (*one * *two); }

///////////////////////////////////////////////////////////////////////////////
// '/' operator
float divide(float *one, float *two){ return (*one / *two); }

///////////////////////////////////////////////////////////////////////////////
// main() loop
int main(int argc, char *argv[])
{
        char *usage = 
        "\nCalcul v1.0 [author: msc]\n"\
        "=========================\n"\
        "Usage: calcul number operator number\n"\
        "operators: + - x / m (add, subtract, multiply, divide, "
        "exponentiation)\n"\
        "e.g. calcul 12.3 / 45.6";

        if (argc != 4) // er moeten 4 argumenten (inc. programma) ingegeven zijn.
        {
                puts(usage); // geef aan hoe het werkt
                return 1;
        }

        #ifdef DEBUG // debug output if wanted
                printf("debug-output: \nargc=%d\n", argc);
                int i;
                for (i=0; i<argc; i++)
                        printf("%d-%s\n", i, argv[i]);
        #endif

        float one, two, result;
        char operator;
        float (*pfoperator)(float *one, float *two);

        one = atof(argv[1]);
        operator = argv[2][0];
        two = atof(argv[3]); 
 
        switch(operator)
        {
        case '+': pfoperator = plus; break;        
        case '-': pfoperator = minus; break;
        case 'x': pfoperator = multiply; break;
        case '/': pfoperator = divide; break;
        case 'm': pfoperator = mverhef; break;
        default : puts("invalid operand!"); return 0;
        }
       
        // berekenen van resultaat is altijd dezelfde manier dankzij
        // functiepointer
        result = pfoperator( &one, &two); 
        
        printf("\n\t%f %c %f = %f\n", one, operator, two, result);
        return 1;
}
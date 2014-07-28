// ================================
// structs test
// demonstrates structure handling
// author: msc
// ================================
#include <stdio.h>
#include <stdlib.h>

#define AANTAL    4
#define SIZE_NAAM 12

//==============================================================================
// voorbeeld-structuurtje
typedef struct student 
{
    char naam[SIZE_NAAM];
    int  nr;
} STUDENT, *PSTUDENT;

// we maken een array van structs aan, die we later vullen
STUDENT sarray[AANTAL];

// hier maken we een array van structs aan die we direct vullen
STUDENT sarray2[] = 
{
   "Fritz",   2240,
   "Gerhard", 7794,
   "Uwe",     1143,
   "\0",      0     // hoeft niet, wel handig om loops af te sluiten     
};                  // je loopt gewoon de array door tot je NULL tegenkomt...

// we maken een 2-dimensionale array van structs aan, die we later vullen
STUDENT s2darray[AANTAL][AANTAL];

//==============================================================================


// demonstreert toekennen van waarden aan struct-members
void fill_stud_array(void)
{
    // maak geheugen schoon, alle bytes op 0 zetten
    memset(sarray, 0, sizeof(sarray));
     
    // nu kan ik elk afzonderlijk element van de array zo benaderen
    strcpy(sarray[0].naam, "Saskia"); // zie de .
    sarray[0].nr = 123;
    
    // of zo....
    strcpy((sarray+1)->naam, "Judith"); // zie de ->
    (sarray+1)->nr = 9999;
    
    // of zo.....
    STUDENT *ps = &sarray[2];   // pointer ps wijst naar 3e element
    strcpy(ps->naam, "Birgit"); 
    ps->nr = 2002;
    
    // of zelfs zo...
    ps = sarray+3;               // pointer wijst naar 4e element 
    strcpy(ps->naam, "Gertrud"); 
    ps->nr = 9898;
}       


// output op simpele manier met .
void display_stud_array(void)
{
    puts("methode 1");
    int i;
    for (i=0; i<AANTAL; i++)
        if (sarray[i].naam[0] != 0) // als eerste char 0 is, bestaat ie niet...
            printf ("naam=%s,\t nr=%d\n", sarray[i].naam, sarray[i].nr);
}     


// output met ->
void display_stud_arrayp(void)
{
    puts("\nmethode 2");
    int i;
    PSTUDENT ps;            // zelfde als STUDENT * ps;
    ps = sarray;            // pointer staat op startadres van sarray, dus 1e element!
    
    for (i=0; i<AANTAL; i++)
        if ((ps+i)->naam[0] != 0) // als eerste char 0 is, bestaat ie niet...
            printf ("naam=%s,\t nr=%d\n", (ps+i)->naam, (ps+i)->nr);
    
    puts("\nmethode 3");
   
    // of, door gewoon de pointer op te hogen... 
    for (i=0; i<AANTAL; ps++, i++)
        if (ps->naam[0] != 0) // als eerste char 0 is, bestaat ie niet...
            printf ("naam=%s,\t nr=%d\n", ps->naam, ps->nr);   
}     


// output alleen met pointers, array als argument meegegeven
void display_stud_arrayp2(STUDENT *ps)
{
    puts("\nmethode 4, zonder teller, maar laatste element moet dan wel 0 zijn");
    
    for (; ps->naam[0]; ps++) // deze methode kan niet met sarray (overflow)
            printf ("naam=%s,\t nr=%d\n", ps->naam, ps->nr);   
}     


// demonstreert het kopieren van geheugen
void demo_copy_array(void)
{
    puts("\ncopy array");
    PSTUDENT sarray3 = (PSTUDENT)malloc(sizeof(sarray2)); // alloceren
    memcpy(sarray3, sarray2, sizeof(sarray2));            // copy geheugen
    
    display_stud_arrayp2(sarray3);
           
    free(sarray3);                                        // vrijmaken
}


// demonstreert handling van 2-dim array
void demo_2dims()
{
     int i, j, k = 0;
     puts ("\n2 dim demo:");
     PSTUDENT ps = (PSTUDENT)s2darray;
     for (i=0; i<AANTAL; i++)
         for (j=0; j<AANTAL; j++)
         {
             ps->nr = k++;
             printf("[%d][%d] %d\n", i, j, ps->nr);
             ps++;
         }           
}     

int main(void)
{
    fill_stud_array();               // 1. data handling
    
    display_stud_array();            // 2. display method 1
    display_stud_arrayp();           // 3. display method 2
    display_stud_arrayp2(sarray2);   // 4. display method 3     

    demo_copy_array();               // 5. memcpy demo
    demo_2dims();                    // 6. 2-dim demo
    
    puts ("Press a key\a");
    getchar();
    return 0;
}
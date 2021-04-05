#include<stdio.h> 
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools.h"
#include "validations.h"

int main(int argc,char*argv[]) 
{
    if( !Validate_Args(argc))  return EXIT_FAILURE; 
 
    FILE * fp = fopen(argv[1],"r"); 

    if( ! Validate_File(fp,argv[1]))  return EXIT_FAILURE; 
 
    /*
    quantities [0] => Total orders
    quantities [1] => Num orders  of 2 dish
    quantities [2] => Num orders  of 3 dish
    quantities [3] => Num orders  of 4 dish
    quantities [4] => Total ingredients
    */
    int quantities[5];
    char ingredients[30][20];  

    Set_Quantities(fp,quantities);
   
    int totalmembers = 2*quantities[1]+3*quantities[2]+4*quantities[3];
    int solutionVector[ quantities[0] ] ;
    int permutation[ quantities[0] ] ;
    int totalDiffIngred = 0;

    InitializeArray(quantities[0],solutionVector);
    InitializeArray(quantities[0],permutation);   
    Set_Ingredients(fp,30,20,ingredients,&quantities[4]);

    int orders [ quantities[4] ] [ quantities[0] ] ;

    Set_Matrix(argv[1],quantities[4], quantities[0] ,orders,30,20,ingredients);
    Set_SolutionVector(quantities, quantities[4], quantities[0], orders,  permutation, 0, totalmembers-1,solutionVector,  &totalDiffIngred);
  
    SendToFile(totalDiffIngred,quantities,solutionVector,quantities[4], quantities[0], orders,30,20, ingredients);

    return 0;
}
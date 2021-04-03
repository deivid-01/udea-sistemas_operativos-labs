#include<stdio.h> 
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools.h"

int main(int argc,char*argv[]) 
{

    if( !Validate_Args(argc))  return EXIT_FAILURE; 
 
    FILE * fp = fopen(argv[1],"r"); 

    if( ! Validate_File(fp))  return EXIT_FAILURE; 


    char ingredients[30][15];   
    /*
    quantities [0] => Total orders
    quantities [1] => Num orders  of 2 dish
    quantities [2] => Num orders  of 3 dish
    quantities [3] => Num orders  of 4 dish
    quantities [4] => Total ingredients
    */
    int quantities[5];

    Set_Quantities(fp,quantities);
    
    int totalmembers = 2*quantities[1]+3*quantities[2]+4*quantities[3];
    int solutionVector[ quantities[0] ] ;
    int permutation[ quantities[0] ] ;

    InitializeArray(quantities[0],solutionVector);
    InitializeArray(quantities[0],permutation);

    int totalDiffIngred = 0;
    Set_Ingredients(fp,30,15,ingredients,&quantities[4]);


    int orders [ quantities[4] ] [ quantities[0] ] ;

    Set_ValuesMatrix(quantities[4], quantities[0] ,orders,30,15,ingredients);


    Find_SolutionVector(quantities,
                        quantities[4],
                        quantities[0],
                        orders,
                        permutation,
                        0,
                        totalmembers-1,
                        solutionVector,
                        &totalDiffIngred);
  
  
    SendToFile_Matrix(quantities[4], quantities[0] ,orders);
    Send_VectorS(solutionVector,  quantities[0] );

    Send_Ingredients(totalDiffIngred);
    Send_Orders(quantities,solutionVector,quantities[0], quantities[4], orders, ingredients);


    return 0;
}
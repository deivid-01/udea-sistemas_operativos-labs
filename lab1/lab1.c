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
    int totalOrders;
    int totalIngredients =  0 ;
    int cost = 26;
    int solutionVector[]={0,1,2,3,4,5,6,7,8};


    Set_TotalOrders(fp,&totalOrders);
    Set_Ingredients(fp,30,15,ingredients,&totalIngredients);

    int orders [ totalIngredients ] [ totalOrders ] ;

    Set_ValuesMatrix(totalIngredients,totalOrders,orders,30,15,ingredients);

    //Set_SolutionVector()
    
    SendToFile_Matrix(totalIngredients,totalOrders,orders);

    Send_VectorS(solutionVector, totalOrders);
    Send_Ingredients(cost);

    return 0;
}
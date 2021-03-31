#include<stdio.h> 
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools.h"

int main(int argc,char*argv[]) 
{

    if( argc < 2) {   printf("You must specify a filepath" );  return EXIT_FAILURE; }
 

    FILE * fp = fopen(argv[1],"r"); //OPening file 

    if ( !fp){  printf("Error opening file %s\n",argv[1]);   return EXIT_FAILURE;} //Validation

 
    char line[1024];
    char ingredients[30][15];
    int totalIngredients, totalOrders, lineCount, wordCount;
    totalIngredients =  0 ;
    int cost = 26;
    int vectorSolucion[]={0,1,2,3,4,5,6,7,8};


    totalOrders= GetTotalOrders(fp);

    #pragma region GetTotalIngredients()
    lineCount = 0;
    fp = fopen(argv[1],"r");
    while(fgets(line,1024,fp))  //Reading each line of file
    {
        char *word ;
        char *rest = line; // Points to the direction the line
        wordCount = 0;

        while( word = strtok_r(rest," ",&rest) ) // Reading each word of line
        {          
            if ( lineCount > 0 && wordCount > 0 )
            {                 
                bool newIngredient = true ;  

                for (int i = 0; i < totalIngredients; i++)
                {
                    int min = strlen(word)>strlen(ingredients[i]) ? strlen(ingredients[i]) : strlen(word);

                    if ( strncmp(ingredients [ i ] ,word,min)== 0){ newIngredient = false ; break; }                    
                }
  
                if ( newIngredient ) 
                {                    
                   strcpy(ingredients[totalIngredients],word);
                    totalIngredients ++;
                }                  
            }
              wordCount ++;
        }     
        lineCount ++;     
    }
    fclose(fp); 

    #pragma endregion
         
    #pragma region SetValues_Matrix()
    fp = fopen(argv[1],"r");
    int orders [ totalIngredients ] [ totalOrders ] ;
    line[1024];
    lineCount = 0;

    while(fgets(line,1024,fp))  //Reading each line of file
    {    
        if( lineCount >= 1 )
        {    
            for (int i = 0; i < totalIngredients; i++)
            {             
                char copy [1024];;
                memcpy(copy,line,strlen(line));

                bool ingFound = false;
                wordCount = 0;
                char *word ;
                char *rest = copy;
                        
                while( word = strtok_r(rest," ",&rest) )  // Reading each word of line
                {        
                    if(  wordCount > 0 )
                    {
                        int min = strlen(word)>strlen(ingredients[i]) ? strlen(ingredients[i]) : strlen(word);

                        if( strncmp(ingredients [ i ] ,word,min)== 0 )
                        {                         
                            orders [ i ] [ lineCount - 1 ] = 1; ingFound = true; break;                          
                        }
                    }
                    wordCount ++;          
                }
                if(!ingFound) { orders [ i ] [ lineCount - 1 ] = 0; }                 
            }
        }                      
        lineCount ++;
    }
    
    fclose(fp); // Close file
    #pragma endregion

    SendToFile_Matrix(totalIngredients,totalOrders,orders);
    Send_VectorS(vectorSolucion, totalOrders);
    Send_Ingredients(cost);
    
    

    
    //Create
 
   

//Enviar al archivo
 







    return 0;
}
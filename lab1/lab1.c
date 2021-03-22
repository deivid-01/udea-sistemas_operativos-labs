#include<stdio.h> 
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
int main(int argc,char*argv[]) 
{
    if( argc < 2)
    {
        printf("You must specify a filepath" );
        return EXIT_FAILURE;
    }

    FILE * fp = fopen(argv[1],"r"); //OPening file 

    if ( !fp){  printf("Error opening file %s\n",argv[1]);} //Validation


   
    char line[1024];
     char ingredients[30][15];
    int totalIngredients = 0;
    int totalOrders = 0;
    int lineCount = 0;
    int wordCount;

    #pragma region GetEachLineOfFile()
    while(fgets(line,1024,fp))  //Reading each line of file
    {
        char *word ;
        char *rest = line; // Points to the direction the line
         //rest -> first value of thre array
         // &rest -> direction the memory of the pointer

         //Strtik_g gets the value of rest and then point rest to the next value of the line after a " "
        wordCount = 0;
        #pragma region GetEachWordOfLine()
        while( word = strtok_r(rest," ",&rest) ) // Reading each word of line
        {
            #pragma region SetTotalOrders()
            if ( lineCount == 0 && wordCount == 0 ) { totalOrders = atoi(word) ; break; }
            #pragma endregion
            
            #pragma region SetTotalIngredients()
            else if ( lineCount > 0 && wordCount > 0 )
            {
              //  printf(" Word: %s\n",word); 
               
                bool newIngredient = true ; 

                #pragma region SearchIngredientInList()

                for (int i = 0; i < totalIngredients; i++)
                {
                        int min = 0;
                        if(strlen(word)>strlen(ingredients[i]))
                        {
                        min = strlen(ingredients[i]);
                        }
                        else{
                            min  = strlen(word);
                        }
        

                    if ( strncmp(ingredients [ i ] ,word,min)== 0){ newIngredient = false ; break; }                    
                }

                #pragma endregion
               

                #pragma region AddIngredientToList()
                if ( newIngredient ) 
                {
                    
                    strcpy(ingredients[totalIngredients],word);


                // printf("Ing: %s |  Word: %s\n",ingredients[totalIngredients] ,word);
                    totalIngredients ++;
                } 
                #pragma endregion                        
            }
            #pragma endregion

              wordCount ++;
        }
        
        #pragma endregion
        
        lineCount ++;

      
    }


         
    

    #pragma endregion

    fclose(fp); // Close file

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
                          int min = 0;
                        if(strlen(word)>strlen(ingredients[i]))
                        {
                        min = strlen(ingredients[i]);
                        }
                        else{
                            min  = strlen(word);
                        }
        

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


    #pragma region Send Matrix to output.txt

    fp= fopen ( "output.txt", "w" );

    fputs("Esta es la matriz de los platos:\n\n" , fp );


    for (int i = 0; i < totalIngredients; i++)
    {
        char data [ totalOrders + 8]; // + # ??
        
        for (int j = 0; j < totalOrders; j++)
        {       
            data [ j ] = orders [ i ] [ j ]  + '0';
        }
     
        fputs(strcat ( data , ( i == 0 )  ? "\n" : "" ) , fp );

    }
 


    #pragma endregion


    

    return 0;
}
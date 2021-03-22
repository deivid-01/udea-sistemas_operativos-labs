#include<stdio.h> 
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>

int GetTotalOrders(FILE *fp )

{
    char line[1024];
     int wordCount = 0;
     int lineCount = 0;

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
            if ( lineCount == 0 && wordCount == 0 ) { return atoi(word) ; }
            #pragma endregion
            
           
              wordCount ++;
        }
        
        #pragma endregion
        
        lineCount ++;

      
    }
}


void SendToFile_Matrix(int totalIngredients,int totalOrders, int(*orders)[])
{
    FILE *fp= fopen ( "output.txt", "w" );



    fputs("Esta es la matriz de los platos:\n\n" , fp );
    
     for (int i = 0; i < totalIngredients; i++)
    {
        char data [ totalOrders +8 ]; // + # ??
        
        for (int j = 0; j < totalOrders; j++)
        {       
            data [ j ] =*(*(orders ) + (i*totalOrders +j) ) + '0';
        }
     
        fputs(strcat ( data , ( i == 0 )  ? "\n" : "" ) , fp );

    }
    
    fclose(fp);
}

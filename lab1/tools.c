#include<stdio.h> 
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>

void Set_TotalOrders(FILE* fp,int *totalOrders )

{
    rewind(fp);
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
            if ( lineCount == 0 && wordCount == 0 ) { *totalOrders =  atoi(word) ; }
            #pragma endregion
            
           
              wordCount ++;
        }
        
        #pragma endregion
        
        lineCount ++;

      
    }
}

void Set_Ingredients(FILE* fp,int rows, int cols, char ingredients[][cols],int *totalIngredients)
{
    rewind(fp);

    char line[1024];
    int  lineCount = 0;
    int wordCount = 0;




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

                for (int i = 0; i < *totalIngredients; i++)
                {
                    int min = strlen(word)>strlen(ingredients[i]) ? strlen(ingredients[i]) : strlen(word);

                  
                    if ( strncmp(ingredients [ i ] ,word,min)== 0){ newIngredient = false ; break; }                    
                }
  
                if ( newIngredient ) 
                {                    
                   strcpy(ingredients[*totalIngredients],word);
                    *totalIngredients = *totalIngredients + 1;
                }                  
            }
              wordCount ++;
        }     
        lineCount ++;     
    }

    
    
    fclose(fp); 

}

void Set_ValuesMatrix(int rows_ord, int cols_ord,int orders[][cols_ord],int row_ing, int col_ing, char ingredients[][col_ing])
{
    FILE *fp = fopen("input.txt","r");
    char line[1024];
    int lineCount = 0;
    int wordCount = 0;
    
    while(fgets(line,1024,fp))  //Reading each line of file
    {    
        if( lineCount >= 1 )
        {    
            for (int i = 0; i < rows_ord; i++)
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

void Send_VectorS(int vectorSolucion[], int totalOrders){
    
    FILE * fp = fopen( "output.txt", "a+");

    fputs("\n\n Este es el vector de solución: ", fp);
    char data[totalOrders];

    for (int i = 0; i < totalOrders; i++)
        {       
            data[i] =  vectorSolucion [ i ];
            fprintf(fp, "%d", data[i]); 
        }

     fclose(fp);
}

void Send_Ingredients(int totalIngredients){
    
    FILE * fp = fopen( "output.txt", "a");
    int total= totalIngredients;
    fprintf(fp,"\n\nLa cantidad de ingredientes diferentes totales es: %d", total );
    fclose(fp);
}

//------------------------------------------------------Validation---------------------------------------//
bool Validate_Args(int argc)
{
     if ( argc < 2) 
     {
        printf("You must specify a filepath" );
        return false;
     }

     return true;
     
}

bool Validate_File(FILE *fp)
{
    if ( !fp){  printf("Error opening file %s\n"); return false;}

    return true;

}
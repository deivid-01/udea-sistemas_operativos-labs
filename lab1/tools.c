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

void Set_Quantities(FILE* fp, int quantities[])
{
    rewind(fp);
    char line[1024];
    int wordCount = 0;
    char *word ;
    fgets(line,1024,fp);
    char *rest = line; 

    while( word = strtok_r(rest," ",&rest) ) // Reading each word of line
    {           
        quantities[wordCount] =  atoi(word) ;     

        wordCount ++;
    }

}

void Set_Ingredients(FILE* fp,int rows, int cols, char ingredients[][cols],int *totalIngredients)
{
    rewind(fp);

    char line[1024];
    int  lineCount = 0;
    int wordCount = 0;

    *totalIngredients = 0;


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

void SendToFile_Matrix(int totalIngredients,int totalOrders,int orders[][totalOrders])
{
     FILE *fp= fopen ( "output.txt", "w" );



    fputs("Esta es la matriz de los platos:\n\n" , fp );
   
    
     for (int i = 0; i < totalIngredients; i++)
    {        
        for (int j = 0; j < totalOrders; j++)
        {       
           char num[2];
           sprintf(num, "%u", orders[i][j]);
           
            fputs(num,fp);
        }

        fputs( "\n", fp );

    }

    
    fclose(fp);
}

//Sending the solution vector to the file 

void Send_VectorS(int vectorSolucion[], int totalOrders){
    
    FILE * fp = fopen( "output.txt", "a+");

    fputs("\nEste es el vector de solución: ", fp);
    char data[totalOrders];

    for (int i = 0; i < totalOrders; i++)
        {       
            data[i] =  vectorSolucion [ i ];
            fprintf(fp, "%d\t", data[i]); 
        }

     fclose(fp);
}

//Sending the total ingredients to the file 

void Send_Ingredients(int totalIngredients){
    
    FILE * fp = fopen( "output.txt", "a");
    int total= totalIngredients;
    fprintf(fp,"\n\nLa cantidad de ingredientes diferentes totales es: %d", total );
    fclose(fp);
}



void Send_Orders(int quantities[], int solutionVector[], int totalOrders, int totalIngredients, int orders[][totalOrders], char ingredients[]){
    FILE * fp= fopen("output.txt", "a");
    int offset_2, offset_3, offset_4, temp, ord_0, ord_1, ord_2, temp1, temp2;
    
    offset_2= quantities[1];
    offset_3= quantities[2];
    offset_4= quantities[3];

    fputs("\nEl pedido 0 contiene:", fp);
    fputs("\nEl pedido 1 contiene:", fp);
    fputs("\nEl pedido 2 contiene:", fp);

   
   for(int i=0; i<= totalIngredients; i++){
         ord_0 = solutionVector[offset_2*2];
            for(int u=0; u<= ord_0; u++){
                temp=  solutionVector[u];
                if(orders[i][temp] == 1){
                   if (fgets(ingredients[i], 60, fp)!= NULL){
                        fprintf (fp,"%d", ingredients[i]);
                   }
                } temp ++;
            }
            ord_1= solutionVector[offset_3*3];
            for(int w=ord_0+1; w<= ord_1; w++){
                temp1= solutionVector[w];
                if(orders[i][temp1]==1){
                    if(fgets(ingredients[i], 60, fp)!= NULL){
                        fprintf(fp, " %d", ingredients[i]);
                    } temp1 ++;
                }
            }
            ord_2=  solutionVector[offset_4*4];
            for(int y=ord_2+1; y<= ord_2; y++){
                temp2= solutionVector[y];
                if(orders[i][temp2]==1){
                    if(fgets(ingredients[i], 60, fp)!= NULL){
                         fprintf(fp, " %d", ingredients[i]);
                    } temp2++;
                }
            }

        

    }
   
}

int Swap ( int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void InitializeArray(int size,int arr[])
{
        for (int i = 0; i < size; i++)
    {
        arr[i]=i;
   
    }
    
}

int Calculate_Cost(int *quantities,int rows,int cols,int orders[][cols],int *temp_sol)
{
           
    int cost = 0;
    int offset_t3 = 2*quantities[1];
    int offset_t4 = offset_t3 + 3*quantities[2];
    for (int i = 0; i < quantities[1]; i++)
    {
        for (int  j = 0; j < quantities[4]; j++)
        {
            int m= temp_sol[2*i];
            int m_1 = temp_sol[2*i + 1];
            cost = cost + (orders[j][m] | orders[j][m_1]);
         
        }
        
    }
    
  
      for (int i = 0; i < quantities[2]; i++)
    {
        for (int  j = 0; j < quantities[4]; j++)
        {
             
            int m= temp_sol[3*i+offset_t3];
             
            int m_1 = temp_sol[3*i+offset_t3+ 1];
            
            int m_2 = temp_sol[3*i+offset_t3+ 2];
           
       
   
            cost = cost + (orders[j][m] | orders[j][m_1] | orders[j][m_2] ) ;
        }
        
    }

      for (int i = 0; i < quantities[3]; i++)
    {
        for (int  j = 0; j < quantities[4]; j++)
        {
            int m= temp_sol[4*i+offset_t4];
            int m_1 = temp_sol[4*i+offset_t4+ 1];
            int m_2 = temp_sol[4*i+offset_t4+ 2];
            int m_3 = temp_sol[4*i+offset_t4+ 3];
            cost = cost + (orders[j][m] | orders[j][m_1] | orders[j][m_2] | orders[j][m_3] ) ;
        }
        
    }


    return cost;
    
}


void Find_SolutionVector(int *quantities,int rows,int cols,int orders[][cols],int *arr,int start,int end,int *sol,int*bestCost)
{
   
    int currentcost  = 0;
    if (start==end)
    if(1)
    {
            currentcost = Calculate_Cost(quantities,rows,cols,orders,arr);
        
            if(currentcost >*bestCost)
            {
               

                *bestCost = currentcost;
                for (int k = 0; k < end + 1; k++)
                {
                    sol[k] =arr[k];
                }
                
                
            }
            return;
    }
    int i;
    for(i = start;i<=end;i++)
    {
            Swap((arr+1),(arr+start));
            Find_SolutionVector(quantities,rows,cols,orders,arr,start+1,end,sol,bestCost);
            Swap((arr+i),(arr+start));
    }
    
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
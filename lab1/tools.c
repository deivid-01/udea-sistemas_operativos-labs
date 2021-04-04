#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void Set_Quantities(FILE *fp, int quantities[])
{
    rewind(fp);
    char line[1024];
    int wordCount = 0;
    char *word;
    fgets(line, 1024, fp);
    char *rest = line;

    while (word = strtok_r(rest, " ", &rest)) // Reading each word of line
    {
        quantities[wordCount] = atoi(word);

        wordCount++;
    }
}

void Set_Ingredients(FILE *fp, int rows, int cols, char ingredients[][cols], int *totalIngredients)
{
    rewind(fp);

    char line[1024];
    int lineCount = 0;
    int wordCount = 0;

    *totalIngredients = 0;

    while (fgets(line, 1024, fp)) //Reading each line of file
    {

        char *word;
        char *rest = line; // Points to the direction the line
        wordCount = 0;

        while (word = strtok_r(rest, " ", &rest)) // Reading each word of line
        {
            if (lineCount > 0 && wordCount > 0)
            {
                bool newIngredient = true;

                for (int i = 0; i < *totalIngredients; i++)
                {
                    int min = strlen(word) > strlen(ingredients[i]) ? strlen(ingredients[i]) : strlen(word);

                    if (strncmp(ingredients[i], word, min) == 0)
                    {
                        newIngredient = false;
                        break;
                    }
                }

                if (newIngredient)
                {
                    strcpy(ingredients[*totalIngredients], word);
                    *totalIngredients = *totalIngredients + 1;
                }
            }
            wordCount++;
        }
        lineCount++;
    }

    fclose(fp);
}

void Set_ValuesMatrix(char fileName[], int rows_ord, int cols_ord, int orders[][cols_ord], int row_ing, int col_ing, char ingredients[][col_ing])
{
    FILE *fp = fopen(fileName, "r");
    char line[1024];
    int lineCount = 0;
    int wordCount = 0;

    while (fgets(line, 1024, fp)) //Reading each line of file
    {
        if (lineCount >= 1)
        {
            for (int i = 0; i < rows_ord; i++)
            {
                char copy[1024];
                ;
                memcpy(copy, line, strlen(line));

                bool ingFound = false;
                wordCount = 0;
                char *word;
                char *rest = copy;

                while (word = strtok_r(rest, " ", &rest)) // Reading each word of line
                {
                    if (wordCount > 0)
                    {
                        int min = strlen(word) > strlen(ingredients[i]) ? strlen(ingredients[i]) : strlen(word);

                        if (strncmp(ingredients[i], word, min) == 0)
                        {
                            orders[i][lineCount - 1] = 1;
                            ingFound = true;
                            break;
                        }
                    }
                    wordCount++;
                }
                if (!ingFound)
                {
                    orders[i][lineCount - 1] = 0;
                }
            }
        }
        lineCount++;
    }

    fclose(fp); // Close file
}

void SendToFile_Matrix(int totalIngredients, int totalOrders, int orders[][totalOrders])
{
    FILE *fp = fopen("output.txt", "w");

    fputs("Esta es la matriz de los platos:\n\n", fp);

    for (int i = 0; i < totalIngredients; i++)
    {
        for (int j = 0; j < totalOrders; j++)
        {
            char num[2];
            sprintf(num, "%u", orders[i][j]);

            fputs(num, fp);
        }

        fputs("\n", fp);
    }

    fclose(fp);
}

//Sending the solution vector to the file

void Send_VectorS(int vectorSolucion[], int totalOrders)
{

    FILE *fp = fopen("output.txt", "a+");

    fputs("\nEste es el vector de solución: ", fp);
    char data[totalOrders];

    for (int i = 0; i < totalOrders; i++)
    {
        data[i] = vectorSolucion[i];
        fprintf(fp, "%d\t", data[i]);
    }

    fclose(fp);
}

//Sending the total ingredients to the file

void Send_Ingredients(int totalIngredients)
{

    FILE *fp = fopen("output.txt", "a");
    int total = totalIngredients;
    fprintf(fp, "\n\nLa cantidad de ingredientes diferentes totales es: %d", total);
    fclose(fp);
}

void Send_Orders(int quantities[], int solutionVector[], int rows_ord, int cols_ord, int orders[][cols_ord], int rows_ing, int cols_ing, char ingredients[][cols_ing])
{

    FILE *fp = fopen("output.txt", "a");

    int offset_2 = 0;
    int offset_3 = 0;
    int offset_4 = 0;

    for (int i = 0; i <= 2; i++)
    {
        char num[1];
        fputs("\n\nEl pedido ", fp);
        fputs(itoa(i, num, 10), fp);
        fputs(" contiene: ", fp);

        int idxs[quantities[i + 1] * (i + 2)];
        int count = 0;
        //Set indexes
        for (int j = 0; j < quantities[i + 1]; j++)
        {
            for (int q = 0; q < (i + 2); q++)
            {
                int idx;

                if (i == 0)
                {
                    offset_2 = q + j * 2;
                    idx = solutionVector[offset_2];
                }

                else if (i == 1)
                {
                    offset_3 = offset_2 + q + j * 3 + 1;
                    idx = solutionVector[offset_3];
                }

                else if (i == 2)
                {
                    offset_4 = offset_3 + q + j * 4 + 1;
                    idx = solutionVector[offset_4];
                }

                idxs[count] = idx;
                count = count + 1;
            }
        }
        //Find ingredients with index

        int n = sizeof(idxs) / sizeof(idxs[0]);

        for (int t = 0; t < rows_ord; t++)
        {
            bool ingredientExist = false;

            for (int q = 0; q < n; q++)
            {
                if (orders[t][idxs[q]])
                {
                    ingredientExist = true;
                    break;
                }
            }
            //Send to file
            if (ingredientExist)
            {
                fputs(ingredients[t], fp);
                fputs(" ,", fp);
            }
        }
        fputs("\n", fp);
    }

    printf("\nThe output.txt file has been created successfully\n");
    printf(" ");

    fclose(fp);
}

int Swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void InitializeArray(int size, int arr[])
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }
}

int Calculate_Cost(int *quantities, int rows, int cols, int orders[][cols], int *temp_sol)
{

    int cost = 0;
    int offset_t3 = 2 * quantities[1];
    int offset_t4 = offset_t3 + 3 * quantities[2];
    for (int i = 0; i < quantities[1]; i++)
    {
        for (int j = 0; j < quantities[4]; j++)
        {
            int m = temp_sol[2 * i];
            int m_1 = temp_sol[2 * i + 1];
            cost = cost + (orders[j][m] | orders[j][m_1]);
        }
    }

    for (int i = 0; i < quantities[2]; i++)
    {
        for (int j = 0; j < quantities[4]; j++)
        {

            int m = temp_sol[3 * i + offset_t3];

            int m_1 = temp_sol[3 * i + offset_t3 + 1];

            int m_2 = temp_sol[3 * i + offset_t3 + 2];

            cost = cost + (orders[j][m] | orders[j][m_1] | orders[j][m_2]);
        }
    }

    for (int i = 0; i < quantities[3]; i++)
    {
        for (int j = 0; j < quantities[4]; j++)
        {
            int m = temp_sol[4 * i + offset_t4];
            int m_1 = temp_sol[4 * i + offset_t4 + 1];
            int m_2 = temp_sol[4 * i + offset_t4 + 2];
            int m_3 = temp_sol[4 * i + offset_t4 + 3];
            cost = cost + (orders[j][m] | orders[j][m_1] | orders[j][m_2] | orders[j][m_3]);
        }
    }

    return cost;
}

void Find_SolutionVector(int *quantities, int rows, int cols, int orders[][cols], int *arr, int start, int end, int *sol, int *bestCost)
{

    int currentcost = 0;
    if (start == end)
        if (1)
        {
            currentcost = Calculate_Cost(quantities, rows, cols, orders, arr);

            if (currentcost > *bestCost)
            {

                *bestCost = currentcost;
                for (int k = 0; k < end + 1; k++)
                {
                    sol[k] = arr[k];
                }
            }
            return;
        }
    int i;
    for (i = start; i <= end; i++)
    {
        Swap((arr + 1), (arr + start));
        Find_SolutionVector(quantities, rows, cols, orders, arr, start + 1, end, sol, bestCost);
        Swap((arr + i), (arr + start));
    }
}

//------------------------------------------------------Validation---------------------------------------//

bool IsANumber(char number[])
{

    int n =  strlen(number);
    
    for (int i = 0; i <n; i++)
    {
        int num = (int)number[i];
     
        if( i == ( n-1))    {if ( num == 10){ continue;}}
    
        if (num <= 47 || num >= 58){ return false;}       
    }
    return true;
}

bool ValidCharacters(char word[])
{
        int n =  strlen(word);
    
    for (int i = 0; i <n; i++)
    {
        int num = (int)word[i];
     
        if( i == ( n-1))  {  if ( num == 10){ continue;}}

        if(num ==95){ continue;}
        
        if (num <= 96 || num >= 123){ return false;}
      
    }
    return true;
}

void ErrorMessage()
{
    printf("ERROR FILE: File format is not allowed\n");
}


bool Validate_Args(int argc)
{
    if (argc < 2)
    {
        printf("You must specify a filepath");
        return false;
    }

    return true;
}

bool Validate_File(FILE *fp, char fileName[])
{
    int sizeFirstLine = 4;
    int sumFirstLine = 0;
    int firstNumber;

    if (!fp)
    {
        printf("ERROR FILE:  opening file %s\n", fileName);
        return false;
    }

    char line[1024];
    int lineCount = 0;


    while (fgets(line, 1024, fp)) //Reading each line of file
    {
 
        char *word;
        char *rest = line; // Points to the direction the line
        int wordCount = 0;   

        if ( lineCount == 0)
        {
            while (word = strtok_r(rest, " ", &rest)) // Reading each word of line
            {
                if ( !IsANumber(word) || wordCount > 3 ){ break;}
                
            
                if (wordCount == 0) {  firstNumber = atoi(word); }
              
                if ( wordCount>0) { sumFirstLine += (wordCount+1)*atoi(word);}
                
                wordCount++;      
            }
            if (wordCount != sizeFirstLine | firstNumber != sumFirstLine)         
             {   ErrorMessage(); return false;}    
                          
        }
        else
        {
            while (word = strtok_r(rest, " ", &rest)) // Reading each word of line
            {
                if (wordCount == 0)
                { if (!IsANumber(word) ) {  ErrorMessage(); return false;}    }
                else
                {
                    if ( strlen(word)>20 || !ValidCharacters(word)){ ErrorMessage(); return false;}
                } 

                wordCount++;      
            }          
        }
        lineCount++;
    }
   
   if((lineCount-1)!=firstNumber) { ErrorMessage();return false;}

    return true;
}


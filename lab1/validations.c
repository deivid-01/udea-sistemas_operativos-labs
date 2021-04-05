#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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


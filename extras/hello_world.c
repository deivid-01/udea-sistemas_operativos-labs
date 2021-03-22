#include<stdio.h> //Standard input/ouput
#include<stdlib.h> //standard (?)
#include <string.h>
int main(int argc,char*argv[]) // argc: Size argv[] | argv*[0] = "nameFile.c" | 
{
    if( argc < 2)
    {
        //Send to standard output or print("You must specifiy a filepathh")
        // %s -> string
        // %d -> numeric value
        printf("You must specify a filepath %s\n ",argv[0]);
    }

    return 0;
}
#include<stdio.h> 

#define TOOLS_h

void Set_Quantities(FILE *, int[]);
void Set_Ingredients(FILE *,int, int, char(*)[],int *);

void Set_Matrix(char[],int, int ,int (*)[],int, int, char(*)[]);

void Set_SolutionVector(int *,int ,int ,int (*)[],int *,int,int,int *,int*);

void InitializeArray(int ,int []);

void SendToFile(int ,int [],int [],int , int , int (*)[],int ,int , char (*)[]);



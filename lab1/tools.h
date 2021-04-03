#include<stdio.h> 

#define TOOLS_h

 int Set_TotalOrders(FILE *, int *);
void Set_Quantities(FILE *, int[]);
void Set_Ingredients(FILE *,int, int, char(*)[],int *);

void Set_ValuesMatrix(int, int ,int (*)[],int, int, char(*)[]);

void Find_SolutionVector(int *,int ,int ,int (*)[],int *,int,int,int *,int*);

void SendToFile_Matrix(int,int, int (*)[]);

void Send_Ingredients(int);

void Send_Orders(int [], int [], int , int , int (*)[], char (*)[]);

void Send_VectorS(int [], int);
void InitializeArray(int ,int []);


bool Validate_Args(int);
bool Validate_File(FILE *);
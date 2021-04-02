#include<stdio.h> 

#define TOOLS_h

 int Set_TotalOrders(FILE *, int *);

void Set_Ingredients(FILE *,int, int, char(*)[],int *);

void Set_ValuesMatrix(int, int ,int (*)[],int, int, char(*)[]);


void SendToFile_Matrix(int,int, int (*)[]);

void Send_Ingredients(int);

void Send_VectorS(int [], int);


bool Validate_Args(int);
bool Validate_File(FILE *);
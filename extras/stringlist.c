#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    //static list:
    const char *a[2];

    a[0] = "oda";
   // a[1] = "oda ";

   // printf("%d",a[0]=="oda");
    

    
   // printf("%s\n",a[0]);

    //Change values of list :
    char array[30][10];
  
    strcpy(array[0],"oda");
    strcpy(array[1],"oda ");
      
     printf("%d",strcmp(array[0],array[1]));
    return 0;
}
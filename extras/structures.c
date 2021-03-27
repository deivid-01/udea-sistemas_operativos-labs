#include <stdio.h>
#include <string.h>

struct  GoldenVect{
    int x0;
    int x1;
    int x2;
    int value;

};



int main()
{
   struct GoldenVect  GoldenVect[2];

    GoldenVect[0].x0 = 0;
    GoldenVect[0].x1 = 1;
    GoldenVect[0].x2 = 2;
    GoldenVect[0].value = 85;


    GoldenVect[1].x0 = 10;
    GoldenVect[1].x1 = 11;
    GoldenVect[1].x2 = 22;
    GoldenVect[1].value = 845;

    for (int i = 0; i < 2; i++)
    {
        printf("%d\n",GoldenVect[i].x0);
        printf("%d\n",GoldenVect[i].x1);
        printf("%d\n",GoldenVect[i].x2);
        printf("%d\n",GoldenVect[i].value);
        printf("-----------\n");
    }
    




    

   
    return 0 ;
}
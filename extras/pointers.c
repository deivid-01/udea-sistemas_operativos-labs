#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    int num = 20;
    //int -> Type of variable your want  point to
    //*p -> asterik to declarate pointers
    //& - > get direction of a variable

    int *p =&num; //p points to num;

    printf("P Value: %d",*p); // Prints num value
    printf("Address of num :%d",p); // Prints num address

    num+=10;

    printf("P Value: %d",*p); // p updates its value with the new num

    *p+=10;

    printf("Num Value: %d\n",num); // numupdates its value with the new *p
    
   //With arrays

   int nums[2]; 

    nums[0] = 4;
    nums[1] = 5;

   int *pp = nums; // Iniciatilization without &

    printf("%d",&pp); //Points to the first value of the array


    return 0;
}
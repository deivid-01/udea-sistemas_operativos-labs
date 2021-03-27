#include <stdio.h>

int max = 0;
int maximum = 0;
void combinationUtil(int (*orders)[],int goldV [],int arr[], int totalIngredients, int totalOrders,int data[], int start, int end,
                     int index, int r)
{


    if (index == r)
    {
        int sum = 0;
          //  printf("data[0]: %d | data[1]: %d\n",data[0],data[1]);
                
            for (int i = 0; i < totalIngredients; i++) 
            {
                int  a = *(*(orders ) + (i*totalOrders +data[0] ) );
                int  b = *(*(orders ) + ( i*totalOrders +data[1]) );
                
                
               // printf("i: %d, j: %d\n",a,b);
                
                if (a || b)
                    sum = sum + 1;    
            }
      
        if( sum > max && data[0]+data[1]>maximum)
        {   printf("data[0]: %d | data[1]: %d\n",data[0],data[1]);
            printf("Sum: %d | max: %d\n",sum,max);
            max = sum;
            goldV[0] = data[0];
            goldV[1] = data[1];
            
          //  printf("data[0]: %d | data[1]: %d\n",data[0],data[1]);
           

        }
        return;
    }
  

    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(orders,goldV,arr, totalIngredients,totalOrders,data, i+1, end, index+1, r);
    }
}



void printCombination(int (*orders)[],int goldV[],int arr[],int totalIngredients,int totalOrders, int start,int n, int r)
{  
    int data[r];   

    combinationUtil(orders,goldV,arr, totalIngredients, totalOrders, data, start, n-1, 0, r) ;

    return;

}
  


int main()
{
    int totalIngredients = 10;
    int totalOrders = 9;
    int orders[10][9]=
    {
        {1,0,0,1,0,0,0,0,0},
        {1,0,1,1,0,1,1,1,1},
        {1,0,0,1,0,0,0,0,0},
        {1,1,0,1,1,0,0,0,0},
        {1,1,0,1,1,0,0,0,0},
        {0,1,0,0,1,0,0,0,0},
        {0,1,0,0,1,0,0,0,0},
        {0,1,1,0,1,1,1,1,1},
        {0,0,1,0,0,1,1,1,1},
        {0,0,1,0,0,1,1,1,1}
    };
    int arr[totalOrders];

    for (int i = 0; i < totalOrders; i++)
    {
        arr[i] = i ;
    }
    int r = 2;
    int n = sizeof(arr)/sizeof(arr[1]);
    int goldV[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};

    printCombination(orders,goldV,arr,totalIngredients,totalOrders,0, n, r);
 
    printf("%d",goldV[0]);
}


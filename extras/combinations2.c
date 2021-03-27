// Program to print all combination of size r in an array of size n
#include <stdio.h>
#include <stdbool.h>



struct GoldenVect {
    int data[50];
    int sum;
};

struct GoldenVect GoldenVects[37];

int actualGolden= 0;
int sumCom = 0;
int umbral = 4;
int offset = 0;

void combinationUtil(int (*combi)[],int arr[], int data[],int sizeArr, int start, int end, 
                     int index, int r);
  
// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(int (*combi)[],int arr[], int n, int r)
{

    if ( r > umbral )
        return;
    // A temporary array to store all combination one by one
    int data[r];
  
    // Print all combination using temprary array 'data[]'
    combinationUtil(combi,arr, data,n, 0, n-1, 0, r);
  /*
    offset = 2;
    int indxSub  = 0;
    int subarr[n-r];

    for (int xx = 0; xx < actualGolden; xx++)
    {
        for (int i = 0; i < n; i++)
        {
            bool band= false;
            
            for (int j = 0; j < r; j++)
            {
                if ( arr[i] ==GoldenVects[xx].data[j] )
                {
                    band = true;
                    break;
                } 
            }

            if( !band )
            {
                subarr[indxSub] = arr[i];
                indxSub = indxSub +1 ;
            }
        }
        
        int data[r+1];
        combinationUtil(combi,subarr, data,n-r, 0, (n-r)-1, 0, r+1);
        offset = offset + 3;
    }
*/

}

void combinationUtil(int (*combi)[],int arr[], int data[], int sizeArr,int start, int end,
                     int index, int r)
{
    // Current combination is ready to be printed, print it
    if (index == r)
    {
         for (int i = 0; i < r; i++)
        {
             
            printf("%d",data[i]);
            

        }
        sumCom = sumCom + 1;
        printf("\nSum: %d\n",sumCom);
       /*
        for (int i = 0; i < r; i++)
        {
             
            GoldenVects[actualGolden].data[offset+i] = data[i];
            

        }
        
       actualGolden = actualGolden + 1;
        
        */
        return ;
    }
  
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        
        data[index] = arr[i];
        combinationUtil(NULL,arr, data, sizeArr,i+1, end, index+1, r);
        
        

    }
}

int main()
{
    int arr[] = {4,6,7,8};
    int r = 4;
    int n = sizeof(arr)/sizeof(arr[0]);
    printCombination(NULL,arr, n, r);

   /*
    for (int j = 0; j < actualGolden; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            printf("%d",GoldenVects[j].data[i]);
        }

        printf("\n");

    }
    */
}
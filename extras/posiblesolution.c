#include <stdio.h>

void print_array(int arr[], int size)
{
    int i;
    for ( i = 0; i < size; i++)
    {
        printf("%d\t",arr[i]);
    }

    printf("\n");
    
}



void swap ( int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int calculate_cost(int *quantities,int rows_i,int cols_i,int pizzas[][cols_i],int *temp_sol)
{
    
  //  for (int i = 0; i < rows_i; i++)
    //{
   // printf("%d\n",pizzas[1][0]); 
    //}
    
    
    int cost = 0;
    int offset_t3 = 2*quantities[1];
    int offset_t4 = offset_t3 + 3*quantities[2];
    for (int i = 0; i < quantities[1]; i++)
    {
        for (int  j = 0; j < quantities[4]; j++)
        {
            int m= temp_sol[2*i];
            int m_1 = temp_sol[2*i + 1];
            cost = cost + (pizzas[j][m] | pizzas[j][m_1]);
         
        }
        
    }

      for (int i = 0; i < quantities[2]; i++)
    {
        for (int  j = 0; j < quantities[4]; j++)
        {
            int m= temp_sol[3*i+offset_t3];
            int m_1 = temp_sol[3*i+offset_t3+ 1];
            int m_2 = temp_sol[3*i+offset_t3+ 2];
            cost = cost + (pizzas[j][m] | pizzas[j][m_1] | pizzas[j][m_2] ) ;
        }
        
    }

      for (int i = 0; i < quantities[3]; i++)
    {
        for (int  j = 0; j < quantities[4]; j++)
        {
            int m= temp_sol[4*i+offset_t4];
            int m_1 = temp_sol[4*i+offset_t4+ 1];
            int m_2 = temp_sol[4*i+offset_t4+ 2];
            int m_3 = temp_sol[4*i+offset_t4+ 3];
            cost = cost + (pizzas[j][m] | pizzas[j][m_1] | pizzas[j][m_2] | pizzas[j][m_3] ) ;
        }
        
    }


    return cost;
    
}

void solve(int *quantities,int rows_i, int cols_i,int pizzas[][cols_i],int *arr,int start,int end, int *sol, int *bestcost)
{
 //   printf("holas");
    int currentcost  = 0;
    if (start==end)
    if(1)
    {
            currentcost = calculate_cost(quantities,rows_i,cols_i,pizzas,arr);
            if(currentcost >*bestcost)
            {
               

                *bestcost = currentcost;
                for (int k = 0; k < end + 1; k++)
                {
                    sol[k] =arr[k];
                }
                
                
            }
            return;
    }
    int i;
    for(i = start;i<=end;i++)
    {
            swap((arr+1),(arr+start));
            solve(quantities,rows_i,cols_i,pizzas,arr,start+1,end,sol,bestcost);
            swap((arr+i),(arr+start));
    }
}

void test(int rows,int cols, int arr[][cols])
{
      printf("%d\n",arr[1][0]); 
}


int main()
{
    int pizzas[10][9]=
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
    int quantities[5]= {9,1,1,1,10};
    int totalmembers = 2*quantities[1]+3*quantities[2]+4*quantities[3];
    int sol[]={5,6,8,7,3,2,1,0,4};
    int permut[]= {1,0,8,3,4,6,5,7,2};
    int bestCost = 0;
/*
    for (int i = 0; i < totalmembers; i++)
    {
        sol[i] = i;
        permut[i] = i;
    }*/
    solve(quantities,quantities[4],quantities[0],pizzas,permut,0,totalmembers-1,sol,&bestCost);
    printf("Este es el vector de solucion: ");
    print_array(sol,totalmembers);
    printf("Cost: %d\n: ",bestCost);

   //test(10,0,pizzas);
    

    return 0;
}
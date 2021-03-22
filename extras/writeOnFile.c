#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    FILE *fp= fopen ( "output.txt", "w" );

    int orders[4][5] = {
        {1,2,3,4,5},
        {6,7,8,9,3},
        {6,7,8,9,3},
        {1,2,3,4,5},

    };

 char line[6]; 

 for (int i = 0; i < 4; i++)
 {
   
    
    for (int j = 0; j < 5; j++)
    {       
        line[j] = orders[i][j] + '0';
    }
    fputs(strcat (line, ( i == 0 )  ? "\n" : "" ),fp);
 }
 



    fclose( fp );
 

    return 0;
}
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
    
    
    struct timeval starting_time;
    struct timeval ending_time;

    gettimeofday(&starting_time, NULL);
 
    int id = fork(); //Create a child

    if( id == 0) //Child process
    {
        int num_args = argc;

        if (num_args > 1) // User send commands
        {
            char *args[ num_args];

            for (int i = 1; i < argc; i++)
            {
                args[i -1] = argv[i]; //Set args to execution
            }

            args[num_args-1] = NULL;

            if ( execvp(args[0],args) ) //Execution
                {
                    char error_message[ 30 ] = "An error has ocurred\n" ;
                    write(STDERR_FILENO, error_message, strlen(error_message));	//Display error
                }
        }
        else
        {
            char alert_message[ 30 ] = "No command executed\n" ;
            write(STDERR_FILENO, alert_message, strlen(alert_message));	//Display alert
        }
 
    } 
    else    //Father procress
    {
        wait(NULL); // Waits until child ends

        gettimeofday(&ending_time, NULL);

        //microseconds to seconds
        double elapsed_time_sec =(double) (ending_time.tv_usec - starting_time.tv_usec)/1000000;

        printf("\nElapsed time: %lf s\n",elapsed_time_sec);
    }
    
    
	
}

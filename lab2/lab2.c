#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commandtools.h"


const int MAX_SIZE = 100;
const char ERROR_MESSAGE[128] = "An error has occurred\n";

int main (int argc, char *argv[])
{

	if( argc-1 == 0) //Interactive mode
	{
		interactiveMode();	
	}
	else if ( (argc-1) == 1 ) // Batch mode
	{
		batchMode(argv);
	}
	else //Error
	{
		write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));	
	}
	
}

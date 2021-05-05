#include <stdlib.h>
#include <unistd.h>
#include "commandtools.h"
#include <string.h>

int main (int argc, char *argv[])
{
	setDefaultPath();

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

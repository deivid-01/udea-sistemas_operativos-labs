#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commandtools.h"


const int MAX_SIZE = 100;

int main (int argc, char *argv[])
{
	char str[MAX_SIZE];
	char args[30][15];

	do 
	{
		int numArgs = 0;
		printf ( "wish> ");
		fgets(str, MAX_SIZE, stdin); //Gets input

		deleteNewLine(str); // Delete new line symbol '\n'
		setArguments(30,15,args,str,&numArgs); //Get arguments 

		builtin_command command = str_to_command( args[0] );//Gets builtin command

		if ( command != not_command) // BUIT-IN COMMANDS
		{
			executeBuiltInCommand(command,30,15,args,numArgs);
		}
		else //UNIX COMMANDS
		{
			executeUnixCommand(30,15,args,numArgs);	
		}
	}
	while(1);
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commandtools.h"



char multiPath[512][512];
int numberMultiPath=0;
int pathChanged=0;
int pathEmpty=0;
char *path;

char ERROR_MESSAGE[128] = "An error has occurred\n";


 

char *system_path_commands[] = {
	"/bin/",
	//"/usr/bin/",
	NULL
};

void executeCD(int rows, int cols, char args[][cols],int numArgs)
{
	 if(numArgs==1)
	 {
		if(chdir(args[1])!=0)
		{
			write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));		
		}
	}
	else // number of  arguments is  zero  greather than two
	{ 
		write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));	
	}
}



void executePATH(int rows, int cols, char args[][cols],int numArgs)
{
	printf("PATH command is under development...\n");
	//Num args != 1 
	/*
	printf("path  executed\n");
	pathChanged = 1;
	if ( numArgs == 0 )
	{
		pathEmpty=1;
	}
	else if ( numArgs == 1)
	{	
		pathEmpty=0;
		path=strdup(args[1]);

		if ( path[strlen(path)-1]!='/')
		{
				strcat(path,"/");
		}  	
	}
	else
	{ 
		pathEmpty=0;
		for(int i=1;i<=numArgs;i++)
		{
			char *temp=strdup(args[i]);

			if(temp[strlen(temp)-1]!='/')
					strcat(temp,"/");
			
			strcpy(multiPath[i-1],temp);
			numberMultiPath++;
		}

	}
	*/
                                
}

void executeBuiltInCommand(builtin_command command,int rows,int cols,char  args[][cols],int numArgs)
{
	switch ( command )
	{
		case cd_ :				
			executeCD(30,15,args,numArgs);
			break;
		case path_: 					
			executePATH(30,15,args,numArgs);
			break;
		case exit_ : 
			exit(0);
			break;
	}
}



void executeUnixCommand(int rows, int cols, char args[][cols],int numArgs)
{
	int rc=fork(); // Create a new process

	if(rc<0)//Fork Error
	{ 
		printf("Fork failed\n");		
		exit(1); 
	}
	else if ( rc == 0) // It's a child
	{
		char pathToFile[ MAX_SIZE];
		int i = 0;
		int returnedValue = -1;
		while (*(system_path_commands+i)!= NULL && returnedValue == -1) // Search for all PATHS
		{
			strcpy(pathToFile,*(system_path_commands+i)); //Set path route to pathToFile
			strcat(pathToFile,args[0]); //Concatenate PATH + command
			returnedValue= access(pathToFile,X_OK); //Does this command exist ?
			i++;
		}

		if (returnedValue!= -1) // If command exist 
		{
			//Set arguments of the new process---
			char *newProcessArgs[numArgs+2];
			newProcessArgs[0] = strdup(pathToFile);
			for (int i = 1; i < numArgs+1; i++)
			{	
				newProcessArgs[i] = args[i];
			}
			//Last argument to NULL
			newProcessArgs[numArgs+1] = NULL;
			//---------------------------------
			//Execute command
			execvp(newProcessArgs[0],newProcessArgs);
		}
		else //Command doestn't exist
		{
			write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));	//Display error
		}
		
	}
	else //Father waits until his child ends
	{
		wait(NULL);
	}
}

builtin_command str_to_command( char *strcommand)
{
	for (int i = 0; i < 3; i++)
	{
		if ( ! strcmp(commands[i].string_value, strcommand))
		{
			return commands[i].command;
		}
	}

	return not_command;
	
}

void deleteNewLine(char str[])
{
	char *p = str;

	while( *p != '\n')
	{
		p++;
	}
	*p = '\0';
}

void setArguments(int rows,int cols, char args[][cols],char str[],int *numArgs)
{
		char *token;
		char *rest = str;
		while ( token = strtok_r(rest," ",&rest) )
		{	
			strcpy(args[*numArgs],token);
			*numArgs = *numArgs +1;
		}

		*numArgs = *numArgs -1;
}
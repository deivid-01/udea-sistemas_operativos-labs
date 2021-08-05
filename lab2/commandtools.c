#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commandtools.h"


const int MAX_SIZE = 100;
const char ERROR_MESSAGE[128] = "An error has occurred\n";
char *system_path_commands[50]; 

void setDefaultPath()
{
	*system_path_commands = "/bin/";
	*(system_path_commands +1 ) = "/usr/bin/";
	*(system_path_commands +2 ) = NULL;
}
void executeCommand(char line[])
{
	char args[30][15];
	int numArgs = 0;
	
	deleteLastSymbol(line); // Delete new line symbol '\n'
	saveArguments(30,15,args,line,&numArgs); //Get arguments 

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


/*
*@brief Execute  CD - built_in command
*
*	@param	char(*)[] args  	 :		command arguments
*	@param	int numargs  :		numbers of command arguments 
*/

void executeCD(int rows, int cols, char args[][cols],int numArgs)
{
	 if(numArgs==1)
	 {
		if(chdir(args[1])!=0) // If CD is not executed correctly..
		{
			write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));		
		}
	}
	else // number of  arguments is  zero  greather than two
	{ 
		write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));	
	}
}


/*
*@brief Execute PATH - built_in command
*
*	@param	int rows  	 :		rows number  of args list
*	@param	int cols  :		cols  number  of args list
*	@param	char(*)[] args  :		command arguments
*	@param	int numargs  :		numbers of command arguments 
*/
void executePATH(int rows, int cols, char args[][cols],int numArgs)
{
	if ( numArgs== 0 )
	{
		*system_path_commands = NULL;	//Set first to null
	}
	else
	{
		int i = 0;

		while (i<numArgs) // Set new path
		{
			*(system_path_commands+i) = args[i+1];
			i++;
		}
		*(system_path_commands+i) = NULL;
		
	}
                                
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
			if ( execvp(newProcessArgs[0],newProcessArgs) )
			{
				write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));	//Display error
			}
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


char*  deleteHeadTailWhiteSpaces(char *p)
{
	//Delete head white spaces}
	int size = strlen(p);
	
	
	while(*p == ' ')
	{
		p++;
		size--; 
	}
	

	//Move pointer to the end
	for (int i = 0; i < size-1; i++)
	{
		p++;
	}

	//Delete tail white spaces
	while(*p == ' ' || *p == '\n')
	{
		p--; 
		size--;
	}

	//Move pointer to start
	for (int i = size-1; i > 0 ; i--)
	{		
		p--;
	}

	return p;
}


void redirectAndExecutecommand(char *command,char *output_file)
{
	//Configure excute command to send output in file
}


void batchMode(char *fileName[])
{
	char line[1024];

	FILE * fp = fopen(*(fileName+1), "r");
	
	if(fp == NULL)
	{
		write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));		
	}

	while(fgets(line, 1024, fp))
	{
		executeCommand(line);
	} 
	fclose(fp);
}
void interactiveMode(){


	char str[MAX_SIZE];

	do 
	{		
		printf ( "wish> ");
		fgets(str, MAX_SIZE, stdin); //Gets input

		  //Applies split('&') parallel commands
		
		char *token;
		char *rest = str;
		while ( token = strtok_r(rest,"&",&rest) ) 
		{	
			token = deleteHeadTailWhiteSpaces(token);
						
			if ( strchr(token,'>') != NULL ) // Redirection  //token.contains('>')
			{
				char *rest2 = token;

				char *block;
				char *cmd;
				char *output_file;

				int block_num = 0;

				while ( block = strtok_r(rest2,">",&rest2)) // Applies split('>')
				{
					block = deleteHeadTailWhiteSpaces(block);

					if ( block_num == 0) cmd = block;
			
					else if ( block_num == 1) output_file = block;
		
					else
					{
						write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
						break;
					}

					block_num = block_num +1;
				}

				redirectAndExecutecommand( cmd ,output_file );

			}
			else //Normal execution
			{
				//Forks (?)
				executeCommand(token);
			}
			
		
		}
	


		

		
	}
	while(1);
}





builtin_command str_to_command( char *strcommand)
{
	for (int i = 0; i < 3; i++)
	{
		if ( ! strcmp(commands[i].string_value, strcommand)) //If built in command exists...
		{
			return commands[i].command;
		}
	}

	return not_command;
	
}

void deleteLastSymbol(char str[])
{
	char *p = str;

	while(1)
	{
		p++;

		if (*p == '\0')
		{
			break;
		}
		else if (*p == '\n' )
		{
			*p = '\0';
			break;
		}

	}

}

void saveArguments(int rows,int cols, char args[][cols],char str[],int *numArgs)
{
		char *token;
		char *rest = str;
		while ( token = strtok_r(rest," ",&rest) ) //Applies split()
		{	
			strcpy(args[*numArgs],token);
			*numArgs = *numArgs +1;
		}

		*numArgs = *numArgs -1;
}

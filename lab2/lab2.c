#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


void CallingCD()
{
	//Nums args = 1;
	//chdir
	printf("cd executed\n");
}
void CallingPATH()
{
	//Num args != 1 
	printf("path  executed\n");
}

char *system_path_commands[] = {
	"/bin/",
	NULL
};

int  MAX_SIZE = 100;

typedef enum { cd_, path_,exit_, not_command} builtin_command;

const static struct{
	builtin_command command;
	char* string_value;
} commands [] ={
	{cd_, "cd"},
	{path_,"path"},
	{exit_,"exit"}
};

//Finding enum command
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

int main (int argc, char *argv[])
{
	char str[MAX_SIZE];
	do 
	{
		printf ( "wish> ");
		fgets(str, MAX_SIZE, stdin); //Gets input

		//Remove \n
		char *p = str;
		while( *p != '\n')
		{
			p++;
		}
		*p = '\0';

		builtin_command command = str_to_command( str );

		if ( command != not_command) // BUIT-IN COMMANDS
		{
			switch ( command )
			{
				case cd_ :				
					CallingCD();
					break;
				case path_: 					
					CallingPATH();
					break;
				case exit_ : 
					exit(0);
					break;
				default :
					printf("Command not found \n");
					break;
			}

		}
		else //SYSTEM COMMANDS
		{
			///I dont know if this block of code is working...

			int i = 0 ;
			char pathToFile [ MAX_SIZE];
			int returnedValue = -1;
			while ( *(system_path_commands + i )!= NULL && returnedValue == -1)
			{
				strcpy(pathToFile, * ( system_path_commands + 1 ) );
				strcat(pathToFile,str);
				returnedValue = access(pathToFile,X_OK);
				
			}
			///--------------------------------------------------		
		}
	}
	while(1);
}

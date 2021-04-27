#ifndef COMMANDTOOLS_h
#define COMMANDTOOLS_h

extern  const int MAX_SIZE;
typedef enum { cd_, path_,exit_, not_command} builtin_command;

const static struct{
	builtin_command command;
	char* string_value;
} commands [] ={
	{cd_, "cd"},
	{path_,"path"},
	{exit_,"exit"}
};

void executeUnixCommand(int, int , char (*)[],int );
void executeBuiltInCommand(builtin_command ,int ,int ,char  (*)[],int);
void setArguments(int rows,int cols, char args[][cols],char str[],int *numArgs);
builtin_command str_to_command( char *);
void deleteNewLine(char []);

#endif
#ifndef COMMANDTOOLS_h
#define COMMANDTOOLS_h

extern  const int MAX_SIZE;
extern const char ERROR_MESSAGE[128];
extern char *system_path_commands[50]; 
typedef enum { cd_, path_,exit_, not_command} builtin_command;

const static struct{
	builtin_command command;
	char* string_value;
} commands [] ={
	{cd_, "cd"},
	{path_,"path"},
	{exit_,"exit"}
};
void setDefaultPath();
void interactiveMode();
void batchMode(char *[]);

/**
*@brief Execute Unix Commands.
*
*	 Like  ls,mkdir,cp, nano, etc.. 	
*
*	@param	int rows  	 :		rows number  of args list
*	@param	int cols  :		cols  number  of args list
*	@param	char(*)[] args  :		command arguments
*	@param	int numargs  :		numbers of command arguments 
*/
void executeUnixCommand(int, int , char (*)[],int );
/**
*@brief Execute Builtin  Commands.
*
*	 Like  cd,path and exit. 	
*
*	@param	builtin_command builtin_command  	 :		type of builtin_command
*	@param	int rows  :			rows  number  of args list
*	@param	int cols  :			cols  number  of args list
*	@param	char(*)[] args  :	command arguments
*	@param	int numargs  :		numbers of command arguments 
*/
void executeBuiltInCommand(builtin_command ,int ,int ,char  (*)[],int);
/**
*@brief Save input line arguments .
*	
*
*	@param	builtin_command builtin_command  	 :		type of builtin_command
*	@param	int rows  :			rows  number  of args list
*	@param	int cols  :			cols  number  of args list
*	@param	char(*)[] args  :	command arguments
*	@param	int numargs  :		numbers of command arguments 
*/
void saveArguments(int ,int , char (*)[],char [],int *);
/**
*@brief Searchs for  string equivalent of builtin command .
*	
*	@param	builtin_command builtin_command  	 :		type of builtin_command
*/
builtin_command str_to_command( char *);
/**
*@brief Deletes new line symbol.
*	
*	@param	char [] list    :	string
*/
void deleteLastSymbol(char []);

#endif
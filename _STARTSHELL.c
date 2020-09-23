#include "common.h"
#include "definitions.h"

void startShell(){	

	// take commands indefinitely and process them

	while(1){		

		// prompt
		printf("\033[0;36m");
		printf(">>> ");
		printf("\033[0m");

		// take input 
		char *inputLine = readLine();	

		// split into arguments
		char** args = parseLine(inputLine);
		// NOTE : last element of args is NULL		

		// find length of arguments
		int argsLen = findLength(args);					

		if(argsLen<=1){	

			// if no input was given then contiue the loop of taking input			
			continue;

		} else {						

			if(containsAnd(args, argsLen)==1){

				// check if arguments contain '&' at the end (this is for running process in background)

				// fork to execute command in background
				int rc = fork();
				
				if(rc < 0){

					// if fork failed then show error and exit
					showErrorThenExit(ERROR_FORK_FAILED);

				} else if(rc == 0){

					// child process

					// remove '&' from the end of args and treat 'newArgs' as usual 'args'
					char **newArgs = modifyArgs(args);		

					// execute the commands in args 
					// NOTE : argsLen has been reduced by 1 due to removal of '&'						
					executeCommand(newArgs, argsLen-1);

					// kill the child process
					exit(1);

				} else {
				
					// continue the loop for parent process 
					continue;

				}

			} else {

				// execure the commands in args
				executeCommand(args, argsLen);
			}						
		}			
	}
}

char* readLine(){	

	// to read line
	char* inputLine = NULL;

	// buffer size
	size_t bufferLen = 0;	

	// read the line
	int charCount = getline(&inputLine, &bufferLen, stdin);

	if(charCount==-1){	

		// if read was unsuccessful then show error and exit					
		showErrorThenExit(ERROR_READING_LINE);

	} else {

		// getline() reads last character as '\n' so replacing it with end of string
		inputLine[charCount-1]='\0';	

		return inputLine;
	}
}

char** parseLine(char *line){	

	// pointer that advances in char *line
	char *arg = NULL;

	// passing " " as delimiter
	arg = strtok(line, " ");

	// to store splitted string
	char **args;
	args = malloc(sizeof(char *));

	// check for memory allocation failure
	if(!args) showErrorThenExit(ERROR_MEMORY_ALLOCATION);

	// index of the splitted string 
	int index = 0;
	
	// process till the end of the line
	while(arg!=NULL){

		// save the splitted string
		args[index] = arg;		

		// for next iteration
		arg = strtok(NULL, " ");
		index++;		

		// reallocate space to accomodate for next iteration
		args = realloc(args,(index+1)*sizeof(char*));

		// check for memory allocation failure
		if(!args) showErrorThenExit(ERROR_MEMORY_ALLOCATION);
	}

	// making the last element as NULL
	args[index] = NULL;

	return args;
}

void runBinary(char **args){

	// fork to run system binary as a child process
	int rc = fork();

	if(rc<0){
	
		// if fork failed then show error and exit
		showErrorThenExit(ERROR_FORK_FAILED);

	} else if(rc==0){

		// child process

		// execute binary and show error if failed
		if(execvp(args[0], args) < 0){
			showErrorThenExit(ERROR_EXEC_FAILED);
		}
				

	} else {

		// parent process

		// wait for the child process to finish		
		if(waitpid(rc, NULL, 0) < 0){
			showErrorThenExit(ERROR_CHILD_FAILED);
		}
	}
}

int isBuiltIn(char *command){

	// checks if command belongs to BUILT_IN_COMMANDS list and if then at which index

	int builtInIndex = -1;
	for(int i=0;i<LEN_COMMANDS;i++){
		if(strcmp(BUILT_IN_COMMANDS[i], command)==0){
			builtInIndex = i;
			break;
		}
	}

	return builtInIndex;
}

void executeInBuilt(int index, char **args, int argsLen){

	// run the built in command

	if(index==0) _ls(args, argsLen);
	else if(index==1) _grep(args, argsLen); 
	else if(index==2) _cat(args, argsLen); 
	else if(index==3) _mv(args, argsLen); 
	else if(index==4) _cp(args, argsLen); 
    else if(index==5) _cd(args, argsLen); 
	else if(index==6) _pwd(args, argsLen); 
	else if(index==7) _rm(args, argsLen); 
	else if(index==8) _chmod(args, argsLen);
	else if(index==9) _mkdir(args, argsLen);

}

int containsAnd(char **args, int argsLen){

	if(argsLen>=3){

		// argument length must be greater than or equal 3

		// if the second last string in args is '&' then return 1 (Since, last string is NULL)
		if(strcmp(args[argsLen-2], "&")==0) return 1;
	}
	return 0;
}

void executeCommand(char **args, int argsLen){

	// check index in the built in commands	
	int builtInIndex = isBuiltIn(args[0]);
	
	if(builtInIndex==-1){

		// run system binary if command not found
		runBinary(args);

	} else {

		// execute in built in command
		executeInBuilt(builtInIndex, args, argsLen);
	}
}

char** modifyArgs(char** args){

	// to store the new splitted command arguments
	char **newArgs = malloc(sizeof(char *));


	if(!newArgs){

		// check for memory allocation failure
		showErrorThenExit(ERROR_MEMORY_ALLOCATION);

	} else {
				
		int index = 0;

		// process till element is not '&'
		while(strcmp(args[index], "&")!=0){

			// assign 
			newArgs[index] = args[index];

			index++;

			// realloc memory for next iteration	
			newArgs = realloc(newArgs,(index+1)*sizeof(char*));

			// check for memory allocation failure
			if(!newArgs) showErrorThenExit(ERROR_MEMORY_ALLOCATION);
		}

		// mark last element as NULL
		newArgs[index] = NULL;

		return newArgs;
	}
	
}
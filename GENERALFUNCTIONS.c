#include "common.h"
#include "definitions.h"

void showError(const char *errorText){

	// shows given errorText in red color

	printf("\033[0;31m");
	printf("Error: %s",errorText);	
	printf("\033[0m");
}

void showErrorThenExit(const char *errorText){

	// shows given errorText in red color

	printf("\033[0;31m");
	printf("Error: %s",errorText);	
	printf("\033[0m");

	// kill the process
	exit(1);
}

int isDirectory(char *path){

	/*
	
		returns:
	   -1 : Invalid Path
		1 : Directory
		0 : Regulary File		
	
	*/

	// check if given entity at 'path' is directory or file
	struct stat statbuff;

	if(stat(path, &statbuff) < 0){

		return -1;

	} else {

		return !S_ISREG(statbuff.st_mode);

	}
}

int findLength(char **args){	

	// index in args
	int index = 0;

	// last element of args is NULL so checking till that
	while(args[index]!=NULL){
		
		index++;

	}

	return index+1;
}
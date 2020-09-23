#include "common.h"
#include "definitions.h"

void _cat(char** args, int argsLen){
			
	if(argsLen==2) {

		// incomplete arguments
		showError(ERROR_INCOMPLETE_ARGUMENTS);
	}
	else {

		// display contents of all given files one-by-one
		for(int index=1;index<=argsLen-2;index++){
			displayContent(args[index]);
		}		
	}
}

void displayContent(char *path){
	
	int rc = isDirectory(path);
	if(rc < 0){

		// path is invalid
		showError(ERROR_TARGET_DOES_NOT_EXIST);

	} else if(rc > 0){

		// path if of a directory
		showError(ERROR_TARGET_IS_DIRECTORY);

	} else {

		// open the file
		FILE *file = fopen(path, "r");

		if(!file){

			// handle error
			showError(ERROR_SYSTEM_COMMAND_FAILED);

		} else {

			// read file line by line and print
			char* line = NULL;
			size_t bufferLen = 0;

			while(getline(&line, &bufferLen, file)!=-1){
				printf("%s", line);				
			}

			fclose(file);			
		}		
	}
}
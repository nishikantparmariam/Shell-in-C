#include "common.h"
#include "definitions.h"

void _ls(char **args, int argsLen){

	if(argsLen==2){

		// if no directory is given
		displayDirectory(".");

	} else {

		// display contents of all directories one-by-one		
		for(int index=1;index<argsLen-1;index++){
			displayDirectory(args[index]);
		}

	} 
}

void displayDirectory(char *path){

	// scan the directory at path
	struct dirent **files;						
	int countFiles = scandir(path, &files, NULL, alphasort); // alphasort : Sorted in Alphanumeric Order		

	if(countFiles < 0){

		// handle error if path is invalid
		showError(ERROR_DIRECTORY_ACCESS);

	} else {

		// print contents
		for(int i=0;i<countFiles;i++){
			printf("%s\t", files[i]->d_name);			
		}
		printf("\n");

		free(files);
	}		
}
#include "common.h"
#include "definitions.h"

void _cd(char **args, int argsLen){

	if(argsLen==2) {

		// incomplete arguments
		showError(ERROR_INCOMPLETE_ARGUMENTS);

	} else {		

		// check if target is a directory

		int rc = isDirectory(args[1]);
		if(rc < 0){

			// handle error
			showError(ERROR_TARGET_DOES_NOT_EXIST);

		} else if(rc == 0){
			
			// handle error if file
			showError(ERROR_TARGET_IS_FILE);

		} else {

			// change to directory
			if(chdir(args[1]) < 0){

				showError(ERROR_DIRECTORY_ACCESS);

			}	
		}		
	}	
}
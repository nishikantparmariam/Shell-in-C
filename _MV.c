#include "common.h"
#include "definitions.h"

void _mv(char** args, int argsLen){	

	if(argsLen < 4) {

		// incomplete arguments
		showError(ERROR_INCOMPLETE_ARGUMENTS);	

	}
	else {		

		if(argsLen==4){

			// moving a file to a file
			moveFile(args[1],args[2]);

		} else if(argsLen > 4){

			// moving multiple files to a directory

			// destination directory path
			char* destDir = args[argsLen-2];
			
			int rc = isDirectory(destDir);
			if(rc < 0){

				// check if destination is a directory
				showError(ERROR_TARGET_DOES_NOT_EXIST);

			} else if(rc==0){

				// check if destination is a directory
				showError(ERROR_TARGET_IS_FILE);

			} else {

				// move all files one-by-one to destination directory

				for(int index = 1; index <= argsLen-3; index++){		


					// extract the basename of the file and append it to directory name for moving 
					// e.g. FILE : ../temp/a.txt then newPath = [destination directory path] / a.txt

					char *newPath;					
					char *first = destDir;
					char *middle = "/";
					char *second = basename(args[index]);

					// allocate memory for joining these three
					newPath = malloc(3 + strlen(destDir) + strlen(middle) + strlen(second));


					if(!newPath) {
						
						// check for memory allocation failure
						showError(ERROR_MEMORY_ALLOCATION);

					} else {

						// join first + middle + second = newPath

						strcpy(newPath, first);
						strcat(newPath, middle);
						strcat(newPath, second);	

						// move given file to newPath					
						moveFile(args[index],newPath);

						free(newPath);
					}					
				}
			}
		}
	}
}

void moveFile(char *oldPath, char *newPath){

	// move a file from oldPath to newPath
	if(rename(oldPath, newPath) < 0){

		// handle error
		showError(ERROR_SYSTEM_COMMAND_FAILED);
	}
}
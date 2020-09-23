#include "common.h"
#include "definitions.h"

void _rm(char** args, int argsLen){

	if(argsLen==2) {
		
		// incomplete arguments
		showError(ERROR_INCOMPLETE_ARGUMENTS);

	}
	else {		

		// check if arguments contain "-r" flag

		int rOption = 0;				
		for(int index=1;index<=argsLen-2;index++){
			if(strcmp(args[index], "-r")==0){
				rOption = 1;	
				break;			
			}					
		}		

		// delete all files and directories (only if -r flag was passed) one-by-one
		for(int index=1;index<=argsLen-2;index++){

			// check if name is not the flag itself
			if(strcmp(args[index], "-r")!=0) {

				// delete file / directory at path
				deleteAtPath(args[index], rOption);
			}
		}
		
	}
}

void deleteAtPath(char *path, int rOption){

	// deletes file at the path
	// deletes directory at the path only of rOption == 1

	int rc = isDirectory(path);

	if(rc < 0){

		// invalid path
		showError(ERROR_TARGET_DOES_NOT_EXIST);

	} else if(rc > 0){

		// if directory then proceed only if "-r" was passed

		if(rOption==1){

			// delete ALL contents of the file
			deleteAllInDirectory(path, rOption);
			
			// now the directory at path would be empty

			// delete the empty directory			
			if(rmdir(path) < 0){

				// handle error
			 	showError(ERROR_SYSTEM_COMMAND_FAILED);

			}
		} else {

			// handle error
			showError(ERROR_TARGET_IS_DIRECTORY);

		}

	} else {	


		// if file then delete the file at path	with system call

		if(remove(path) < 0){

			// handle error
			showError(ERROR_SYSTEM_COMMAND_FAILED);

		}	
	}
}

void deleteAllInDirectory(char *path, int rOption){	

	// scan the directory	
	struct dirent **files;
	int countFiles = scandir(path, &files, NULL, alphasort);

	if(countFiles < 0){

		// handle error
		showError(ERROR_DIRECTORY_ACCESS);

	} else {

		// delete all files / directories inside this directory

		for(int i=0;i<countFiles;i++){	

			// delete only if it is file/directory (not "./" OR "../")
		
			if(!(strcmp(files[i]->d_name, ".")==0 || strcmp(files[i]->d_name, "..")==0)){

				// generate path of the file/directory inside given 'path'				
				char* newPath;
				char* first = path;
				char* middle = "/";
				char* second = files[i]->d_name; // take only basename of the file/directory

				// allocate memory for joining these three
				newPath = malloc(3 + strlen(first) +  + strlen(middle) +  + strlen(second));

				if(newPath){

					// join first + middle + second = newPath
					strcpy(newPath, first);
					strcat(newPath, middle);
					strcat(newPath, second);	

					// now newPath is either a file/directory then delete it RECURSIVELY using deleteAtPath();
					deleteAtPath(newPath, rOption);			

					free(newPath);	

				} else {
					
					// memory allocation error
					showErrorThenExit(ERROR_MEMORY_ALLOCATION);	

				}
			}				
		}	

	}

	free(files);
}
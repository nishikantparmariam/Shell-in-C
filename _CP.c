#include "common.h"
#include "definitions.h"

void _cp(char** args, int argsLen){	 

	if(argsLen < 4) {
		
		// incomplete arguments
		showError(ERROR_INCOMPLETE_ARGUMENTS);

	}
	else {
		if(argsLen==4){

			// copying a file to a file
			copyFiletoFile(args[1], args[2]);

		} else if(argsLen==5 && (strcmp(args[1], "-r")==0)) {

			// copying a directory to directory with "-r" as the first argument
			copyDirtoDir(args[2], args[3]);

		} else if(argsLen>=5){

			// copying multiple files to destination directory (args[argsLen-2]) one-by-one
			for(int index=1;index<=argsLen-3;index++){

				// copy a file to directory
				copyFiletoDir(args[index], args[argsLen-2]);
			}
		}
	}
}

void copyFiletoFile(char* src, char* dest){

	
	int rc1 = isDirectory(src);
	int rc2 = isDirectory(dest);

	if(rc1 == 0 && rc2 != 1){

		// proceed only if 
		// (src file exists and is a file) AND (dest file may/may not exists but is definitely 'not' an existing directory)

		// open both files
		FILE *srcFile = fopen(src, "r");
		FILE *destFile = fopen(dest, "w");


		if(!destFile || !srcFile){

			// handle error
			showError(ERROR_SYSTEM_COMMAND_FAILED);

		} else {

			// copy file char-by-char 
			char c = fgetc(srcFile);
			while(c!=EOF){
				fputc(c, destFile);
				c = fgetc(srcFile);
			}

			fclose(srcFile);
			fclose(destFile);
		}
	} else {

		// handle error
		showError(ERROR_INVALID_ARGUMENTS);
	}
}

void copyFiletoDir(char *src, char *dest){

	int rc1 = isDirectory(src);
	int rc2 = isDirectory(dest);

	if(rc1 == 0 && rc2 == 1){	

		// proceed only if (src file exists and is a file) AND (dest is an existing directory)

		// newPath will store the path of [src] file in the [dest] directory

		char *newPath;
		char *first = dest;
		char *middle = "/";
		char *second = basename(src); // extrace the basename of the file

		// allocate memory for joining these three
		newPath = malloc(3 + strlen(first) + strlen(middle) + strlen(second));

		if(!newPath) {

			// memory allocation error
			showError(ERROR_MEMORY_ALLOCATION);
		}
		else {

			// join first + middle + second = newPath
			strcpy(newPath, first);
			strcat(newPath, middle);
			strcat(newPath, second);	
			
			// copy file to file

			copyFiletoFile(src,newPath);

			free(newPath);
		}		
	} else {

		// handle error
		showError(ERROR_INVALID_ARGUMENTS);

	}
}

void copyDirtoDir(char *src, char *dest){
	
	int rc1 = isDirectory(src);
	int rc2 = isDirectory(dest);

	if(rc1==1 && rc2!=0){

		// proceed only if - 
		// (src is an existing directory) AND (dest is may/may not be an existing directory but is definitely not an existing file)

		// create [dest] directory if does not exists
		int flag = 0;
		if(rc2==-1){
			if(mkdir(dest, 0777) >= 0){				
				flag = 1;
			}
		} else {
			flag = 1;
		}


		if(flag==1){

			// now [dest] directory exists
			// create a new directory inside [dest] directory with name of [src] directory

			char *newPath;
			char *first = dest;
			char *middle = "/";
			char *second = basename(src); //extract only name of [src] directory

			// allocate memory for joining these three
			newPath = malloc(3 + strlen(first) + strlen(middle) + strlen(second));

			if(!newPath) {
				
				// memory allocation error
				showError(ERROR_MEMORY_ALLOCATION);

			}
			else {

				// join first + middle + second = newPath

				strcpy(newPath, first);
				strcat(newPath, middle);
				strcat(newPath, second);	

				// newPath now indicates the path - [dest]/[src]	

				if(mkdir(newPath, 0777)>=0){

					// copy all 'files' from [src] directory and put inside [dest]/[src]/

					// scan the [src] directory
					struct dirent **files;
					int countFiles = scandir(src, &files, NULL, alphasort);		

					if(countFiles < 0){

						// handle error
						showError(ERROR_DIRECTORY_ACCESS);

					} else {

						// for all files/directories in [src] directory
						for(int i=0;i<countFiles;i++){					

							// filePath stores the entire path to any file/directory in [src]/
							char *filePath;
							char *first = src;
							char *middle = "/";
							char *second = files[i]->d_name;


							filePath = malloc(3 + strlen(first) + strlen(middle) + strlen(second));
							if(!filePath) {

								// memory allocation error
								showError(ERROR_MEMORY_ALLOCATION);
								
							}
							else {

								// join first + middle + second = filePath
								strcpy(filePath, src);
								strcat(filePath, middle);
								strcat(filePath, second);

								// filePath now indicates the entire path of the file

								// process only if it is a file (i.e. copy only files)

								int rc = isDirectory(filePath);	

								if(rc==0){		

									// copy this file to [dest]						
									copyFiletoDir(filePath, newPath);
								}

								free(filePath);
							}														
						}		
					}

					free(files);

				} else {

					// handle error
					showError(ERROR_SYSTEM_COMMAND_FAILED);
					
				}
				free(newPath);
			}			
		} else {

			// handle error
			showError(ERROR_SYSTEM_COMMAND_FAILED);
			
		}
	} else {

		// handle error
		showError(ERROR_INVALID_ARGUMENTS);
	}

}
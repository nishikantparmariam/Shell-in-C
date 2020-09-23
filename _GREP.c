#include "common.h"
#include "definitions.h"

void _grep(char** args, int argsLen){

	if(argsLen==2) {
		
		// incomplete arguments
		showError(ERROR_INCOMPLETE_ARGUMENTS);

	} else if(argsLen==3) {

		// if input file is not given then start reading from the input
		checkGrep(args[1],NULL);
	}
	else {

		// perform grep for each of the given files one-by-one
		for(int index=2;index<=argsLen-2;index++){
			checkGrep(args[1],args[index]);
		}
	}
}

void checkGrep(char *query,char *path){

	if(!path){

		// if no path if mentioned then start reading from the STDIN

		char* line = NULL;
		size_t bufferLen = 0;	
		while(getline(&line, &bufferLen, stdin)!=-1){

			// if line contains query then print line
			if(contains(query,line)==1){
				printf("%s", line);
			}
		}

	} else {
		
		int rc = isDirectory(path);

		if(rc < 0){

			// handle invalid path
			showError(ERROR_TARGET_DOES_NOT_EXIST);

		} else if(rc > 0){

			// if path is a directory
			showError(ERROR_TARGET_IS_DIRECTORY);

		} else {

			// open the file
			FILE *file = fopen(path, "r");

			if(!file){

				// error in opening file
				showError(ERROR_SYSTEM_COMMAND_FAILED);

			} else {

				// read file line-by-line
				char* line = NULL;
				size_t bufferLen = 0;	

				while(getline(&line, &bufferLen, file)!=-1){

					// if line contains query then print line
					if(contains(query,line)==1){
						printf("%s", line);
					}
				}

				fclose(file);

			}		
		}
	}
}

int contains(char* query, char* text){

	/*
		returns:
		1 : if query is a substring of text
		0 : otherwise
	
	*/

	if(!query || !text) return 0;
	else {

		// loop through entire text
		int i = 0;

		while(text[i]!='\0'){

			// check if query is a prefix from text[i]			
			if(checkIfPrefix(query, text+i)==1) return 1;
			i++;
		}
		return 0;
	}
}

int checkIfPrefix(char *query, char *text){

	/*
		returns:
		1 : if query is a prefix of text
		0 : otherwise	

	*/

	if(!query || !text) return 0;

	// if query is "" (empty string) then match with text
	if(strcmp(query, "\"\"")==0) return 1;

	int i = 0;	
	while(query[i]!='\0' && text[i]!='\0'){
		if(text[i]!=query[i]) return 0;
		i++;		
	}

	// if full query has been matched
	if(query[i]=='\0') return 1;	
	else return 0;
}
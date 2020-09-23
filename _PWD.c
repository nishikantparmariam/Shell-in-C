#include "common.h"
#include "definitions.h"

void _pwd(char **args, int argsLen){

	// get the current working directory
	char *output=getcwd(NULL, 0);

	if(output){

		// print the current working directory in green color
		printf("\033[0;32m");
		printf("%s\n", output);
		printf("\033[0m");

	} else {

		// handle error
		showErrorThenExit(ERROR_SYSTEM_COMMAND_FAILED);
	}

	free(output);
}

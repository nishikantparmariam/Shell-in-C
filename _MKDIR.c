#include "common.h"
#include "definitions.h"

void _mkdir(char **args, int argsLen){

	if(argsLen==2) {
		
		// incomplete arguments
		showError(ERROR_INCOMPLETE_ARGUMENTS);

	} else {

		// make the directory
		if(mkdir(args[1], 0777) < 0){

			// handle error
			showError(ERROR_SYSTEM_COMMAND_FAILED);

		}		
	}
}
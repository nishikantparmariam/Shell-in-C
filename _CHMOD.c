#include "common.h"
#include "definitions.h"

void _chmod(char** args, int argsLen){	

	if(argsLen < 4) {

		// incomplete arguments
		showError(ERROR_INCOMPLETE_ARGUMENTS);	

	}
	else {		

		// process the MODE 
		int MODE = processMode(args[1]);
		
		if(MODE!=-1){  

			// change the permissions through system call

			if(chmod(args[2],MODE) < 0){

				// handle error
				showError(ERROR_SYSTEM_COMMAND_FAILED);

			}

		} else {

			// if MODE was invalid then show error
			showError(ERROR_INVALID_ARGUMENTS);

		}		
	}
}

int processMode(char *inputMode){

	/*
		Converts inputMode
		e. g. [1324] to [001 011 010 100] 	

		returns
		-1 : if inputMode is invalid
		MODE : by converting inputMode to correct MODE format needed in chmod

	*/	    

	int MODE = 0;
	int index = 0;
	int isValid = 1;

	// process the whole inputMode char-by-char

	while(inputMode[index]!='\0'){

		int digit = inputMode[index] - '0';		

		// all characters must be digits from [0, 7] otherwise input is invalid

		if(digit>=0 && digit<=7){

			// left shift by three and take OR
			MODE = ((MODE << 3) | digit);

		} else {

			// inputMode is invalid
			isValid = 0;
			break;	
		}

		index++;
	}

	// length must be <=4 and should be valid
	if(index<=4 && isValid==1) return MODE;
	else return -1;
	
}
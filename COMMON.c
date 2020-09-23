#include "common.h"

// declaring global constants
const char *BUILT_IN_COMMANDS[] = {"ls", "grep", "cat", "mv", "cp", "cd", "pwd", "rm", "chmod", "mkdir"};
const int LEN_COMMANDS = 10;

// errors messages
const char* ERROR_INCOMPLETE_ARGUMENTS = "Given arguments are incomplete for this command.\n";
const char* ERROR_TARGET_DOES_NOT_EXIST = "Targeted file/directory does not exist.\n";
const char* ERROR_TARGET_IS_FILE = "Target is a file.\n";
const char* ERROR_TARGET_IS_DIRECTORY = "Target is a directory.\n";
const char* ERROR_MEMORY_ALLOCATION = "Memory allocation error.\n";
const char* ERROR_DIRECTORY_ACCESS = "Directory inaccessible.\n";
const char* ERROR_SYSTEM_COMMAND_FAILED = "System command failure.\n";
const char* ERROR_INVALID_ARGUMENTS = "Given arguments are invalid for this command.\n";
const char* ERROR_FORK_FAILED = "Fork failure.\n";
const char* ERROR_READING_LINE = "Reading line.\n";
const char* ERROR_EXEC_FAILED = "Executing binary failed.\n";
const char* ERROR_CHILD_FAILED = "Child process failed.\n";
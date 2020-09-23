#ifndef COMMON_HEADERS
#define COMMON_HEADERS

#include "common.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

// declaring global constants
extern const char *BUILT_IN_COMMANDS[];
extern const int LEN_COMMANDS;

// errors messages
extern const char* ERROR_INCOMPLETE_ARGUMENTS;
extern const char* ERROR_TARGET_DOES_NOT_EXIST;
extern const char* ERROR_TARGET_IS_FILE;
extern const char* ERROR_TARGET_IS_DIRECTORY;
extern const char* ERROR_MEMORY_ALLOCATION;
extern const char* ERROR_DIRECTORY_ACCESS;
extern const char* ERROR_SYSTEM_COMMAND_FAILED;
extern const char* ERROR_INVALID_ARGUMENTS;
extern const char* ERROR_FORK_FAILED;
extern const char* ERROR_READING_LINE;
extern const char* ERROR_EXEC_FAILED;
extern const char* ERROR_CHILD_FAILED;

#endif
#ifndef FUNCTIONS_DEFINITIONS
#define FUNCTIONS_DEFINITIONS

// general helper functions
void showError(const char *errorText);
void showErrorThenExit(const char *errorText);
int isDirectory(char *path);
int findLength(char **args);

// shell
void startShell();
char* readLine();
char** parseLine(char *line);
void runBinary(char **args);
int isBuiltIn(char *command);
void executeInBuilt(int index, char** args, int argsLen);
int containsAnd(char **args, int argsLen);
void executeCommand(char **args, int argsLen);
char** modifyArgs(char **args);

// LS
void _ls(char** args, int argsLen);
void displayDirectory(char *path);

// GREP
void _grep(char** args, int argsLen);
void checkGrep(char *query,char *path);
int contains(char* query, char* text);
int checkIfPrefix(char *query, char *text);

// CAT
void _cat(char** args, int argsLen);
void displayContent(char *path);

// MV
void _mv(char** args, int argsLen);
void moveFile(char *oldPath, char *newPath);

// CP
void _cp(char** args, int argsLen);
void copyFiletoFile(char *src, char *dest);
void copyFiletoDir(char *src, char *dest);
void copyDirtoDir(char *src, char *dest);

// CD
void _cd(char** args, int argsLen);

// PWD
void _pwd(char** args, int argsLen);

// RM
void _rm(char** args, int argsLen);
void deleteAtPath(char *path, int rOption);
void deleteAllInDirectory(char *path, int rOption);

// CHMOD
void _chmod(char** args, int argsLen);
int processMode(char *inputMode);

// MKDIR
void _mkdir(char** args, int argsLen);

#endif
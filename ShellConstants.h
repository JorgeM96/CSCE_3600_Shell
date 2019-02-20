#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include "SystemCommands.h"
#include "CheckShellMode.h"
#include "NextShellEntryCommand.h"
#include "CommandCharParseProcess.h"
#include "ShellOutputRedirect.h"
#include "ShellPiping.h"
#include "ShellChildProcesses.h"
#define FALSE 0
#define TRUE 1
char *promptSpecialKeywords[] = {"exit","EXIT","cd","CD","pwd","PWD",">",">>","<","<<","~"};
int numPromptKeywords = 11;
FILE *batchFile; // used is shell starts in batch mode instead of interactive mode
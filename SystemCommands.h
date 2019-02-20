// Bultin Functions for Shell program

// Function Declarations
void changeDirectory();
void getWorkingDirectory();
void exitProgram();

// Function Definitions
void ChangeDirectory(char *changedPath)
{
    chdir(changedPath);  
}

void getWorkingDirectory()
{
  char path[4096];
  if(getcwd(path, sizeof(path)) != NULL)
  {
    printf("\nCurrent Working Path is: %s\n", path); // prints the working directory
  }
  else
  {
    printf("Error path cannot be displayed because of a system or permission issue.\n");
  }
}

void exitProgram(int pid) // exists the shell and back to the main BASH shell on the linux system
{
 	printf("\nExiting The Shell...\n");
	kill(pid, SIGINT);
  exit(0);
}
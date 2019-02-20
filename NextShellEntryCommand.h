int nextEntry(FILE *batchFile, int batchMode, int *stop)//,char **CommandLineinput, int* numArgs)
{
	char *userinput = NULL;
  char **Commands = NULL; int pid;
	char characterinput;
	int inputLength = 1;
  int i, j, k;
  int numArgs = 1;
	int *prevCMDEnd = NULL; 
	int sizeCMD;
	int shellCall;
	characterinput = fgetc(batchFile);  //get one character at a time from batchfile

	while((characterinput != '\n') && (characterinput != EOF) && (characterinput != '\0'))
	{					
		// If in Batch Mode, we will read the file line by line and accept the input until the EOF is reached
		// If in Interactive Mode, we will continue to accept input until the '\n' character
		userinput = realloc(userinput, (inputLength + 1) * sizeof(char));	// Dynamically allocate memory to have
		userinput[inputLength - 1] = characterinput;						// enough space to store the input string
		inputLength++;
		characterinput = fgetc(batchFile);
	}

	if(inputLength <= 1)
		userinput = realloc(userinput, (inputLength) * sizeof(char));	// Dynamically allocate memory to have

	userinput[inputLength - 1] = '\0';

	if(batchMode == true)
		printf("%s\n",userinput);

//---------------------------------------------------------------------------------------------
	prevCMDEnd = realloc(prevCMDEnd, sizeof(int));
	prevCMDEnd[0] = 0;

	for(i = 0; i < inputLength; i++)
	{	// Counts the total amount of commands inputted based on how many ';' and '\0' there are
		if((userinput[i] == ';') || (userinput[i]	 == '\0'))
		{
			numArgs++;
			prevCMDEnd = realloc(prevCMDEnd, (numArgs) * sizeof(int));
			prevCMDEnd[numArgs - 1] = i;
		}
	}

	Commands = (char**)calloc(numArgs,sizeof(char*));	// Createss enough space to store the commands separetely
	int l = 0;
	k = 0;
	for(i = 0; i < numArgs - 1; i++)
	{
		sizeCMD = prevCMDEnd[i + 1] - prevCMDEnd[i];
		//printf("Command Size : %i\n", sizeCMD);
		if (sizeCMD > 1)
		{
			Commands[k] = (char*)calloc(sizeCMD + 2, sizeof(char));
			l = 0;
			if((i != 0) && (i != (numArgs -1)))
				l = 1;
			for (j = 0; j < sizeCMD - l; j++)
				Commands[k][j] = userinput[prevCMDEnd[i] + j + l ];
			Commands[k][sizeCMD] = '\0';
			k++;
		}
	}
	
	numArgs = k;
//	for(i = 0; i < numArgs; i++)
//		if (possibleExit(Commands[i]))
//			*ExitCommand = TRUE;
//---------------------------------------------------------------------------------------------
// Forking done here and execution

	int arrayPID[numArgs];
	j = 0;
	for(i = 0; i < numArgs; i++)
	{
		shellCall = chooseChar(Commands[i]);
		if((shellCall >= 3) && (shellCall <= 6))
		{
			switch(shellCall)
			{
				case 3:
				//	Pipelining(Commands[i]);
					break;
				case 4:
					ChangeDirectory(Commands[i]);
					break;
				case 5:
					break;
				default :
					*stop = true;
					break;
			}
		}
		else
		{
			if(strstr(Commands[i],"|"))  //check if they want to pipe
			{
				int a;
				int pipe_count=0;
				char pipe_check[255];
				strcpy(pipe_check,Commands[i]);
				for(a=0;a<sizeof(pipe_check);a++)
				{
					if(pipe_check[a] == '|')
					{
						pipe_count++;
					}
				}
				printf("Pipe count: %d",pipe_count);
				pipeitup(pipe_check);
			}
			
			if(strstr(Commands[i], "CD") || strstr(Commands[i], "cd")) // check if they want to change directories
			{
				
				char chdirectory[255];
				char *dirpath;
				strcpy(chdirectory, Commands[i]);
				
				if(strcmp(chdirectory, "cd") == 0)
				{
					printf("\nNo directory path was passed, changing to home directory...\n\n");
					struct passwd *HomePath = getpwuid(getuid());
					ChangeDirectory(HomePath->pw_dir);
				}
				else if(strcmp(chdirectory, "CD") == 0)
				{
					printf("\nNo directory path was passed, changing to home directory...\n\n");
					struct passwd *HomePath = getpwuid(getuid());
					ChangeDirectory(HomePath->pw_dir);
				}
				else if(strcmp(chdirectory, "cd ") == 0)
				{
					printf("\nNo directory path was passed, changing to home directory...\n\n");
					struct passwd *HomePath = getpwuid(getuid());
					ChangeDirectory(HomePath->pw_dir);
				}
				else if(strcmp(chdirectory, "CD ") == 0)
				{
					printf("\nNo directory path was passed, changing to home directory...\n\n");
					struct passwd *HomePath = getpwuid(getuid());
					ChangeDirectory(HomePath->pw_dir);
				}
				
				dirpath = strtok(chdirectory," ");
				
				int count = 0;
				while(dirpath != NULL)
				{					
					if(count == 1)
					{
						ChangeDirectory(dirpath);
					}
					dirpath = strtok(NULL, " ");
					count++;
				}			
			}
			
			pid = fork();
			arrayPID[j] = pid;
			j++;
			if(pid < 0)
			{
				printf("There was an error trying to fork. Exiting Child Process");
				exit(0);
			}
			else if(pid == 0)
			{			
				if(strstr(Commands[i], "exit") || strstr(Commands[i], "EXIT") || strstr(Commands[i], "Exit"))
				{
					exitProgram(pid);
				}
				childProcess(Commands[i]);
				exit(0);
			}
		}
	}
	
	int status;
	for(i = 0; i < j; i++)
	{
		waitpid(arrayPID[i], &status, 0);
	}

//---------------------------------------------------------------------------------------------
	for(i = 0; i < numArgs; i++)	// Frees the pointers pointing to the inputted commands
			free(Commands[i]);
	free(Commands);		// Release the command pointer back to memory
	free(userinput);	// Releases input string pointer back to memory

	if(characterinput == EOF)//Will set paramenters to exit the program
	{					// if we reach the end of the file
		printf("End of file reached. Exiting program...\n");
		return false;
	}
	else
		return true;
}
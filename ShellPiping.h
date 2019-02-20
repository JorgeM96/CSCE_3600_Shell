// Pipe Test
int pipeitup(char *Commands)
{
	char *PipedCommands = NULL, **CommandLocations = NULL;
	int i, j, TotalCommandsToPipe = 1, CommandsLength = strlen(Commands)+ 1;
	int NewCommandLength = 0, PipeStatus;//, *PipeDescriptor = NULL;
	
	PipedCommands = calloc(CommandsLength, sizeof(char));
	
	for(i = 0; i < CommandsLength; i++)
	{
//		printf("[%c]", Commands[i]);
		if((NewCommandLength == 0) && (Commands[i] == ' '))
		{/*Do nothing*/}
		else if(((i + 1) < CommandsLength)&&(((Commands[i] == ' ')&&(Commands[i+1] == ' '))||(Commands[i] == '|')&&(Commands[i+1] == '|')))
		{/*Do nothing*/}		
		else if(((i - 1) > 0)&&(Commands[i] == ' ')&&(Commands[i-1] == '|'))
		{/*Do nothing*/}
		else if((Commands[i] == ' ')&&((Commands[i+1] == '\0') || (Commands[i+1] == '|')))
		{/*Do Nothing*/}
		else
		{
			PipedCommands[NewCommandLength] = Commands[i];
			if(Commands[i] == '|')
			{
				PipedCommands[NewCommandLength] = '\0';
				TotalCommandsToPipe++;
			}
			NewCommandLength++;
		}
	}
	
	PipedCommands = realloc(PipedCommands, NewCommandLength * sizeof(char));


	CommandLocations = (char**)calloc(TotalCommandsToPipe, sizeof(char*));
	CommandLocations[0] = PipedCommands;
	j = 1;
	for(i = 0; i < NewCommandLength; i++)
	{
		if(((j + 1) < NewCommandLength) && (PipedCommands[i] == '\0'))
		{
			CommandLocations[j] = PipedCommands + i + 1;
			j++;
		}
	}

	
//	PipeDescriptor = calloc(2 * TotalCommandsToPipe, sizeof(int));
//	int PipeDescriptor[TotalCommandsToPipe][2];
	int  TotalPipes = TotalCommandsToPipe -1;
	
	int pid, status;
	
	int PipeFDs[2*TotalPipes];
	
	for (i = 0; i < TotalPipes; i++)
	{
		if(pipe(PipeFDs + i*2) < 0)
			perror("Couldnt open pipes");
	}
	j= 0;
	int k = 0;
	
	char **ArrayofCommands = (char**)calloc(TotalCommandsToPipe,  sizeof(char*));
	int temp;
	for(i = 0; i < TotalCommandsToPipe; i++)
	{
		temp = strlen(CommandLocations[i]);
		ArrayofCommands[i] = (char*)calloc(temp, sizeof(char));
		strcpy(ArrayofCommands[i], CommandLocations[i]);
	}
	

	
	for(i = 0; i< TotalCommandsToPipe; i++)
	{

		pid = fork();
		
		if(pid == 0)
		{

            if(i < TotalPipes)
			{
                if(dup2(PipeFDs[j + 1], 1) < 0)
				{
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            if(j != 0 )
			{
                if(dup2(PipeFDs[j-2], 0) < 0)
				{
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            for(k = 0; k < (2*TotalPipes); k++)
			{
                   close(PipeFDs[k]);
            }

			childProcess(ArrayofCommands[i]);
            exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			j+=2;
		}
	}
	for(i = 0; i < 2 * TotalPipes; i++)
	{
		close(PipeFDs[i]);
	}

	for(i = 0; i < TotalPipes + 1; i++)
	{  
		wait(&status);
	}	
	
	free(PipedCommands);
	
	return;
}
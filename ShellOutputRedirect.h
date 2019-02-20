char *PromptspecialKeywords[] = {"exit","EXIT","cd","CD","pwd","PWD",">",">>","<","<<","~"};

int redirect(char *Commands)
{
	int descriptorF = NULL;
	int i, j;
	int input = 0;
	int output = 0; 
	int sizeFile;
	char *inputFile = NULL, *outputFile = NULL;	
	
	if(strstr(Commands, PromptspecialKeywords[0]) != NULL)
		input = 1;
	if(strstr(Commands, PromptspecialKeywords[1]) != NULL)
		output = 1;
	else if(strstr(Commands, PromptspecialKeywords[2]) != NULL)
		output = 2;
	
	if(input == 1)
	{
		sizeFile = 0;
		for(i = 0; Commands[i] != '<'; i++)
		{
		}
		for(i; (Commands[i] == ' ') || (Commands[i] == '<'); i++)
		{
				Commands[i] = ' ';
		}
		for(i; (Commands[i] != ' ') && (Commands[i] != '\0'); i++)
		{
				sizeFile++;
				inputFile = realloc(inputFile,sizeFile * sizeof(char));
				inputFile[sizeFile - 1] = Commands[i];
				Commands[i] = ' ';

		}
		sizeFile++;
		inputFile = realloc(inputFile,sizeFile * sizeof(char));
		inputFile[sizeFile - 1] = '\0';		
		

		
		if(descriptorF = open(inputFile, O_RDONLY) == -1)
		{
			printf("Couldn't Open file\n");
			exit(EXIT_FAILURE);
		}

		fprintf(stderr, "\nError %d: Loading from \"testing\" file failed: %s\n",
    errno, strerror(errno));

		dup2(descriptorF, 0);
		close(descriptorF);
		
	}	
	if(output > 0)
	{
		sizeFile = 0;

		for(i; (Commands[i] == ' ') || (Commands[i] == '>'); i++)
		{
			Commands[i] = ' ';
		}
		for(i; (Commands[i] != ' ') && (Commands[i] != '\0'); i++)
		{
				sizeFile++;
				outputFile = realloc(outputFile,sizeFile * sizeof(char));
				outputFile[sizeFile - 1] = Commands[i];
				Commands[i] = ' ';
		}
		
		sizeFile++;
		outputFile = realloc(outputFile,sizeFile * sizeof(char));
		outputFile[sizeFile - 1] = '\0';	

		if(output == 1)
			descriptorF = open(outputFile,  O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);	
		else if(output == 2)
			descriptorF = open(outputFile,  O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);	

		dup2(descriptorF, 1);
		close(descriptorF);		
	}
	
	return 1;	
}
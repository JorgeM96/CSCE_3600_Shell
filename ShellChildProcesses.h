char *PromptSpecialkeywords[] = {"exit","EXIT","cd","CD","pwd","PWD",">",">>","<","<<","~"};
int childProcess(char *Commands)
{
	int i = 0;
	int j = 0;
	int callNext = false;
	char *newCMDs = NULL;
	char sizeCMD = NULL;
	char **separate = NULL;
	char	separateAMT = 0;
	redirect(Commands);
	
	for(i = 0; i < strlen(Commands)+1; i++)
	{
		if(checkCommandParse(Commands, j, i))
		{
			newCMDs = realloc(newCMDs, (j + 2)*sizeof(char));
			newCMDs[j] = Commands[i];
			if(Commands[i] == ' ')
			{
				newCMDs[j] = '\0';
				separateAMT++;
			}
			j++;
		}
	}
	sizeCMD = j;
	
	separate = (char**)malloc((separateAMT+2) * sizeof(char*));
	separate[0] = &newCMDs[0];
	separate[separateAMT + 1] = 0;
	j = 1;
	for(i = 0; i <= sizeCMD; i++)
	{
		if ((newCMDs[i] == '\0') && ((i + 1) < sizeCMD))
		{
			separate[j] = &newCMDs[i+1];
			j++;
		}
	}
	separateAMT = j;
	
	for(i = 0; i < 5; i++)		
		if(strstr(Commands, PromptSpecialKeywords[i]) != NULL)
			break;
		

	if (i < 5)
		printf(" ");
	else
	{
		int status = execvp(separate[0], separate);
		if(status == -1)
		{
			printf("%s is not a recognized or valid command.\n", Commands);
		}
	}
	
	free(newCMDs);
	
	return;
}
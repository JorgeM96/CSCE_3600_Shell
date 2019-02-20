char *PromptSpecialKeywords[] = {"exit","EXIT","cd","CD","pwd","PWD",">",">>","<","<<","~"};

bool checkCommandParse(char *Commands, int j, int i)
{
		bool checkParse;
		if((j == 0)&& (Commands[i] == ' '))
		{
			checkParse = false;
		}
		if(((i + 1) < strlen(Commands)) && (Commands[i+1] == ' ') && (Commands[i] == ' '))
		{
			checkParse = false;
		}
		else if((Commands[i] == ' ') && (Commands[i+1] == '\0'))
		{
			checkParse = false;
		}
	else
	{
			checkParse = true;
	}
	return checkParse;
}

int chooseChar(char *Commands)
{
	char *CommandN = malloc((1+ strlen(Commands)) * sizeof(char));
	int chosenChar;
	int i = 0;
	
	strcpy(CommandN, Commands);	// Makes a copy so the original commands are not changed
	
	for(i = 0; i < 11; i++)
	{
		if(strstr(CommandN, PromptSpecialKeywords[i]) != NULL)
		{
			chosenChar = i;
		}
	}
	
	return chosenChar;
}
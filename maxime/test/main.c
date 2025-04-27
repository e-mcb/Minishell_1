#include "test.h"



int main(int argc, char *argv[], char **envp)
{
	int i = 0;
	char *pwd = NULL;

	while (strnstr(envp[i], "PWD=", 4) == NULL) 
		i++;
	pwd = envp[i] + 4;

	char *input;

	// Read a line of input from the user
	while (1) {

		input = readline("minishell> ");
		if (input == NULL) 
		{
			perror("readline");
			return 1;
		}
		if (input[0] != '\0') 
			add_history(input);
		// Check if the input is empty
		if (strlen(input) == 0) 
		{
			free(input);
			continue;
		}
		if (count_quotes(input))
		{
			fprintf(stderr, "Error: Unmatched quotes\n");
			free(input);
			continue;
		}
		// break;
	}

	// Add the input to the history
	add_history(input);

	// Print the input
	printf("You entered: %s\n", input);

	// Free the allocated memory for the input
	free(input);

	return 0;
}
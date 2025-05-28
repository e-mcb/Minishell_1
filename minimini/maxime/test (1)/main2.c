#include "test.h"



// int main(int argc, char *argv[], char **envp)
// {
// 	int i = 0;
// 	char *pwd = NULL;

// 	while (strnstr(envp[i], "PWD=", 4) == NULL) 
// 		i++;
// 	pwd = envp[i] + 4;

// 	char *input;

// 	// Read a line of input from the user
// 	while (1) {

// 		input = readline("minishell> ");
// 		if (input == NULL) 
// 		{
// 			perror("readline");
// 			return 1;
// 		}
// 		if (input[0] != '\0') 
// 			add_history(input);
// 		// Check if the input is empty
// 		if (strlen(input) == 0) 
// 		{
// 			free(input);
// 			continue;
// 		}
// 		if (count_quotes(input))
// 		{
// 			fprintf(stderr, "Error: Unmatched quotes\n");
// 			free(input);
// 			continue;
// 		}
// 		// break;
// 	}

// 	// Add the input to the history
// 	add_history(input);

// 	// Print the input
// 	printf("You entered: %s\n", input);

// 	// Free the allocated memory for the input
// 	free(input);

// 	return 0;
// }

t_token *create_token(char *str)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(str);
	new_token->type = -1;
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}
	

int add_token(t_token **token, char *str, t_token_type type, int rank)
{
	t_token *new_token;
	t_token *current_token;

	// if (str == NULL)
		//TOUT FREE
	new_token = create_token(str);
	if (!new_token)
		return (0);
	new_token->type = type;
	new_token->split_rank = rank;
	if (*token == NULL)
	{
		*token = new_token;
		return (0); //pour erreurs
	}
	
	current_token = *token;
	while (current_token->next != NULL)
		current_token = current_token->next;
	current_token->next = new_token;
	
	return (0);
}


// void tokenize(char *str, t_token **token)
// {
	


// }




// int main (void)
// {
// 	char *str = "echo \"hello world\"";
// 	int i;
// 	t_token *token;
// 	char **splitted;

// 	i = 0;
// 	splitted = ft_split2(str, ' ');
// 	while (splitted[i])
// 	{
// 		tokenize(splitted[i], &token);
// 		i++;
// 	}
	


// }


void test_tokenize(char *str, t_token **token, int rank)
{
	int i;
	int w_start;
	char *tmp;
	bool in_quotes;
	char opening_quote;

	i = 0;
	w_start = -1;
	in_quotes = false;
	while (i <= ft_strlen(str))
	{
		if (w_start < 0 && (str[i] == '\'' || str[i] == '\"') && in_quotes == false)
		{
			in_quotes = true;
			opening_quote = str[i];
			w_start = i;
		}
		else if (w_start >= 0 && (str[i] == '\'' || str[i] == '\"') && in_quotes == false)
		{
			in_quotes = true;
			opening_quote = str[i];
		}
		else if (w_start >= 0 && in_quotes == true && str[i] == opening_quote)
			in_quotes = false;
		if (str[i] != '|' && str[i] != '<' && str[i] != '>' && w_start < 0) // set word start
			w_start = i;
		else if(((str[i] == '|' || str[i] == '<' || str[i] == '>') || i == ft_strlen(str)) && w_start >= 0 && in_quotes == false) //word end
		{
			tmp = ft_substrword(str, w_start, i);
			add_token(token, tmp, TOKEN_TYPE_WORD, rank);
			w_start = -1;
			free(tmp);
		}
		if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && in_quotes == false) 
		{
			if (str[i + 1] && ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))) //check pour append/heredoc
			{
				tmp = ft_substrword(str, i, i + 2);
				if (str[i] == '<')
					add_token(token, tmp, TOKEN_TYPE_HEREDOC, rank);
				else
					add_token(token, tmp, TOKEN_TYPE_APPEND, rank);
				free(tmp);
				i++;
			}
			else
			{
				tmp = ft_substrword(str, i, i + 1);
				if (str[i] == '<')
					add_token(token, tmp, TOKEN_TYPE_REDIRECT_IN, rank);
				else if (str[i] == '>')
					add_token(token, tmp, TOKEN_TYPE_REDIRECT_OUT, rank);
				else if (str[i] == '|')
					add_token(token, tmp, TOKEN_TYPE_PIPE, rank);
				free(tmp);
			}
		}
		i++;
	}
}

// void test_tokenize(char *str, t_token **token, int rank)
// {
// 	int i;
// 	int w_start;
// 	char *tmp;

// 	i = 0;
// 	w_start = -1;
// 	while (i <= ft_strlen(str))
// 	{
// 		if (str[i] != '|' && str[i] != '<' && str[i] != '>' && w_start < 0) // set word start
// 			w_start = i;
// 		else if(((str[i] == '|' || str[i] == '<' || str[i] == '>') || i == ft_strlen(str)) && w_start >= 0) //word end
// 		{
// 			tmp = ft_substrword(str, w_start, i);
// 			add_token(token, tmp, TOKEN_TYPE_WORD, rank);
// 			w_start = -1;
// 			free(tmp);
// 		}
// 		if (str[i] == '<' || str[i] == '>' || str[i] == '|') 
// 		{
// 			if (str[i + 1] && ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))) //check pour append/heredoc
// 			{
// 				tmp = ft_substrword(str, i, i + 2);
// 				if (str[i] == '<')
// 					add_token(token, tmp, TOKEN_TYPE_HEREDOC, rank);
// 				else
// 					add_token(token, tmp, TOKEN_TYPE_APPEND, rank);
// 				free(tmp);
// 				i++;
// 			}
// 			else
// 			{
// 				tmp = ft_substrword(str, i, i + 1);
// 				if (str[i] == '<')
// 					add_token(token, tmp, TOKEN_TYPE_REDIRECT_IN, rank);
// 				else if (str[i] == '>')
// 					add_token(token, tmp, TOKEN_TYPE_REDIRECT_OUT, rank);
// 				else if (str[i] == '|')''
// 					add_token(token, tmp, TOKEN_TYPE_PIPE, rank);
// 				free(tmp);
// 			}
// 		}
// 		i++;
// 	}
// }





int main(void)
{
	t_token *token;

	char *str = "echo \"text\".tx't'\"\"$USER\"\"'' $salut";
	token = NULL;
	char **splitted;
	int i;

	//expand les variables $
	splitted = ft_split2(str, ' ');

	i = 0;

	while (splitted[i])
	{
		// splitted[i] = trim_quotes(splitted[i]);
		printf("splitted[%d]: %s\n", i, splitted[i]);
		test_tokenize(splitted[i], &token, i);
		i++;
	}
	refine_token_type(token);
	while (token)
	{
		printf("Token: %s   token type: %d\n", token->value, token->type);
		token = token->next;
	}
	
	return (0);
}

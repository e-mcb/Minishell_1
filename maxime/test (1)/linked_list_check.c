#include "test.h"

int is_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void refine_token_type(t_token *token)
{
	t_token *current_token;
	t_token *next_token;
	t_token *prev_token;
	bool is_cmd;

	is_cmd = false;
	prev_token = NULL;
	current_token = token;
	while (current_token)
	{
		if (current_token->type == TOKEN_TYPE_PIPE && is_cmd == true)
			is_cmd = false;
		next_token = current_token->next;
		if (current_token->type == TOKEN_TYPE_WORD && prev_token && (prev_token->type == TOKEN_TYPE_REDIRECT_IN || prev_token->type == TOKEN_TYPE_REDIRECT_OUT || prev_token->type == TOKEN_TYPE_APPEND))
			current_token->type = TOKEN_TYPE_FILE;
		else if (current_token->type == TOKEN_TYPE_WORD && prev_token && prev_token->type == TOKEN_TYPE_HEREDOC)
			current_token->type = TOKEN_TYPE_LIMITER;
		else if (current_token->type == TOKEN_TYPE_WORD && next_token &&
			 (next_token->type == TOKEN_TYPE_REDIRECT_IN || next_token->type == TOKEN_TYPE_REDIRECT_OUT || next_token->type == TOKEN_TYPE_APPEND || next_token->type == TOKEN_TYPE_HEREDOC) &&
			  current_token->split_rank == next_token->split_rank && is_digit(current_token->value))
			current_token->type = TOKEN_TYPE_FD;
		else if (current_token->type == TOKEN_TYPE_WORD && is_cmd == false)
		{
			current_token->type = TOKEN_TYPE_CMD;
			is_cmd = true;
		}
		else if (current_token->type == TOKEN_TYPE_WORD)
			current_token->type = TOKEN_TYPE_ARG;
		prev_token = current_token;
		current_token = next_token;
	}
}
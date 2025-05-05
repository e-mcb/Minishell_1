#include "lexer.h"


int main(void)
{
	t_token *token;
	char *str = "echo $USER\"salut les gars\" > out.txt";
	// char *str = "<out.txt cat \'-e 2>salut.txt | cat -e\' | echo salut les >out.txt zgegs >> out.txt << limiter";
	// char *str = "echo $$?$salut$USER,$salut$salut,$USERR$?$salut$";
	// char *str = "cat|cat>out.txt|cat<in.txt|cat>>out.txt|cat<<in.txt|cat>out.txt|cat<in.txt|cat>>out.txt|cat<<in.txt|cat>out.txt|cat<in.txt|cat>>out.txt|cat<<in.txt|cat>out.txt|cat<in.txt|cat>>out.txt|cat<<in.txt";
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
		tokenizer(splitted[i], &token, i);
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
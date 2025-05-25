#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "builtin.h"

int	is_n_flag(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **str, t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (str[i] && is_n_flag(str[i]))
	{
		newline = 0;
		i++;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	if (env_var_exists("_", shell->env) == 1)
		update_env("_", str[i - 1], shell->env);
	else
		shell->env = add_env_var("_", str[i - 1], shell->env);
	shell->exit_status = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->env = NULL;
	shell->exit_status = 0;
	char *test1[] = {"echo", "Hello", "world", NULL};
	char *test2[] = {"echo", "-n", "Hello", "world", NULL};
	char *test3[] = {"echo", "-n", "-n", "Hello", NULL};
	char *test4[] = {"echo", "-n", "-wrong", "Hello", NULL};
	// char *test5[] = {"echo", NULL};
	// char *test6[] = {"echo", "-nnnnnn", "-nnn", NULL};
	char **env;

	shell->env = ft_strdup_array(envp);

	printf("Test 1:\n");
	ft_echo(test1, shell); // => Hello world\n

	printf("Test 2:\n");
	ft_echo(test2, shell); // => Hello world

	printf("Test 3:\n");
	ft_echo(test3, shell); // => Hello

	printf("Test 4:\n");
	ft_echo(test4, shell); // => -wrong Hello\n

	// printf("Test 5:\n");
	// ft_echo(test5, shell); // => \n

	// printf("Test 6:\n");
	// ft_echo(test6, shell); // => \n

	ft_print_array(shell->env);
	return 0;
}
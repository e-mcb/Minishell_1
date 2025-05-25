#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "builtin.h"

int	is_n_flag(char *s)
{
	int	i;
	
	i = 0;
	if (!s)
		return 0;
	if (s[i] != '-')
		return 0;
	i++;
	while (s[i]) {
		if (s[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}

// LE INT RETOURNE EST A STOCKER DANS LE DERNIER CODE RETOUR DU SHELL
// FONCTION DANS LE CAS OU ON PASSE LES ARGUMENTS SANS LE ECHO EN 1
// int	ft_echo(char **str, char **env)
// {
// 	int	i = 0;
// 	int	newline = 1;

// 	if (str == NULL || str[0] == NULL)
// 	{
// 		printf("\n");
// 		update_env("_", "echo", env);
// 		return (0);
// 	}
// 	while (str[i] && is_n_flag(str[i]))
// 	{
// 		newline = 0;
// 		i++;
//     }
// 	while (str[i])
// 	{
// 		printf("%s", str[i]);
// 		if (str[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	if (i > 0)
// 		update_env("_", str[i - 1], env);
// 	else
// 		update_env("_", "echo", env);
// 	if (newline)
// 		printf("\n");
// 	return (0);
// }

// FONCTION DANS LE CAS OU ON PASSE LES ARGUMENTS AVEC LE ECHO EN 1
// RETOURNE LE CODE ERREUR A MODIFIER DANS LA STRUCT SHELL
int	ft_echo(char **str, char **env)
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
	if (i > 1)
		update_env("_", str[i - 1], env);
	else
		update_env("_", "echo", env);
	if (newline)
		printf("\n");
	return (0);
}

int main(int argc, char **argv, char **envp)
{
    char *test1[] = {"Hello", "world", NULL};
    char *test2[] = {"-n", "Hello", "world", NULL};
    char *test3[] = {"-n", "-n", "Hello", NULL};
    char *test4[] = {"-n", "-wrong", "Hello", NULL};
    char *test5[] = {NULL};
    char *test6[] = {"-nnnnnn", "-nnn", NULL};
	char **env;

	env = ft_strdup_array(envp);

    printf("Test 1:\n");
    ft_echo(test1, env); // => Hello world\n

    printf("Test 2:\n");
    ft_echo(test2, env); // => Hello world

    printf("Test 3:\n");
    ft_echo(test3, env); // => Hello

    printf("Test 4:\n");
    ft_echo(test4, env); // => -wrong Hello\n

    printf("Test 5:\n");
    ft_echo(test5, env); // => \n

    printf("Test 6:\n");
    ft_echo(test6, env); // => \n
    return 0;
}
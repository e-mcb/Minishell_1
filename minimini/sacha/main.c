#include "utils.h"
//LE MAIN QUI DUPLIQUE LA VARIABLE ENVIRONNEMENT

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**env_copy;

// 	env_copy = ft_strdup_array(envp);
// 	ft_print_array(env_copy);
// 	ft_free_str_array(env_copy);
// 	return (0);
// }

//********************************************************************************//



// LE MAIN POUR TESTER LES PIPES EN DEBUT ET FIN ET LE NOMBRE DE QUOTES
// int	main(void)
// {
// 	int		result;
// 	char	*str = "    |echo \"te\"xt\".tx't'\"\"$USER\"\"'' $salut  |";

// 	result = ft_starts_or_ends_with_pipe(str);
// 	if (result == 1)
// 		printf("Chaine non valide (pipe en début ou fin)\n");
// 	else
// 		printf("chaine correcte (pas de pipe aux extrmémités)\n");
// 	result = ft_has_invalid_quotes(str);
// 	if (result == 1)
// 		printf("Nombre de quotes incorrect\n");
// 	else
// 		printf("Nombre de quotes correct\n");
// 	return (0);
// }

//********************************************************************************//




// LE MAIN POUR ENLEVER LES QUOTES OUVRANTES ET FERMANTES
//int main(void)
// {
// 	const char *tests[] = {
// 		"'Hello world'",
// 		"\"Hello world\"",
// 		"'He said \"hi\"'",
// 		"\"It's fine\"",
// 		"'Already clean'",
// 		"'Nested 'quotes''",
// 		"'Just one side",
// 		"\"Mismatched'",
// 		NULL
// 	};
// 	int	i;

// 	i = 0;
// 	while (tests[i] != NULL)
// 	{
// 		char *trimmed = ft_remove_wrapping_quotes(tests[i]);
// 		if (trimmed)
// 		{
// 			printf("Input : %s\n", tests[i]);
// 			printf("Output: %s\n\n", trimmed);
// 			free(trimmed);
// 		} 
// 		else
// 		{
// 			printf("Input : %s\nOutput: (null)\n\n", tests[i]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	char *value = ft_getenv(argv[1], envp);
    if (value)
        printf("%s = %s\n", argv[1], value);
    else
        printf("Variable non trouvée.\n");
    return (0);
}

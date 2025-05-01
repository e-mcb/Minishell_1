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

int	main(void)
{
	int		result;
	char	*str = "    |echo \"te\"xt\".tx't'\"\"$USER\"\"'' $salut  |";

	result = ft_starts_or_ends_with_pipe(str);
	if (result == 1)
		printf("Chaine non valide (pipe en début ou fin)\n");
	else
		printf("chaine correcte (pas de pipe aux extrmémités)\n");
	result = ft_has_invalid_quotes(str);
	if (result == 1)
		printf("Nombre de quotes incorrect\n");
	else
		printf("Nombre de quotes correct\n");
	return (0);
}

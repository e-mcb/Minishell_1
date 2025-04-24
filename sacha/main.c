#include "utils.h"

int	main(int argc, char **argv, char **envp)
{
	char	**env_copy;

	env_copy = ft_strdup_array(envp);
	ft_print_array(env_copy);
	ft_free_str_array(env_copy);
	return (0);
}

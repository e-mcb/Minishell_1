#include "builtin.h"

void    ft_write_export(char *str)
{
    int i;

    printf("declare -x ");
    i = 0;
    while (str[i] != 0 && str[i] != '=')
    {
        write(1, &str[i], 1);
        i++;
    }
    if (str[i] == '=')
    {
        write(1, &str[i], 1);
        write(1, "\"", 1);
        i++;
        while(str[i] != 0)
        {
            if (str[i] == '"')
                write(1, "\"", 1);
            write(1, &str[i], 1);
            i++;            
        }
    }
    write(1, "\"", 1);
    write(1, "\n", 1);
}

void ft_print_export(t_shell *shell)
{
    t_envvar    *env_copy;
    
    env_copy = shell->env;
		while (env_copy)
		{
			if (env_copy->exported == 1)
                ft_write_export(env_copy->var);              
			env_copy = env_copy->next;
		}
}

// COMME POUR LES AUTRES FONCTIONS, TOUJOURS ENVOYER export EN PREMIERE LIGNE
// DU TABLEAU
void    ft_export(char **str, t_shell *shell)
{
    int str_size;

    str_size = ft_strsize(str);
    if (!str[1])
    {
        ft_print_export(shell);
        update_or_add("_", str[str_size - 1], shell->env, 0);
		shell->exit_status = 0;
    }        
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
    // t_envvar    *env_copy;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->env = NULL;
	shell->exit_status = 0;
	char *test1[] = {"export", "Hello", "world", NULL};
	char *test2[] = {"export", NULL};

	shell->env = ft_env_to_list(envp);

	ft_export(test1, shell);	
	ft_export(test2, shell);

    // env_copy = shell->env;
	// while (env_copy)
	// {
	// 	printf("%s\n%d\n\n", env_copy->var, env_copy->exported);
	// 	env_copy = env_copy->next;
	// }

	return 0;
}

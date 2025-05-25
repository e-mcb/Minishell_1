#include "builtin.h"

void remove_var(char *var_name, char ***envp_ptr)
{
    char    **envp;
    int     size;
    int     i;
    int     j;

    envp = *envp_ptr;
    size = ft_strsize(envp);
    i = 0;
    while (i < size)
    {
        if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0
            && envp[i][ft_strlen(var_name)] == '=')
        {
            free(envp[i]);
            j = i;
            while (j < size - 1)
            {
                envp[j] = envp[j + 1];
                j++;
            }
            envp[size - 1] = NULL;
            size--;
            continue ;
        }
        i++;
    }
    return ;
}


// VERIFIER LE COMPORTEMENT DE UNSET QUAND AUCUN ARGUMENT
int ft_unset(char **args, char ***env_ptr)
{
    int i;

    if (args[1] == NULL)
    {
        update_env("_", "unset", *env_ptr);
        return (0);
    }
    i = 1;
    while (args[i])
    {
        remove_var(args[i], env_ptr);
        i++;
    }
    update_env("_", args[i - 1], *env_ptr);
    return (0);
}

int main(int argc, char **argv, char **envp) {
    int env_count = ft_strsize(envp);

    char **my_env;

	my_env = ft_strdup_array(envp);

    // Exemple d’appel comme dans un shell
    char *cmd[] = {"unset", "PATH", "HOME", "PWD", NULL};

    printf("Avant unset:\n");
    ft_print_array(my_env);

    ft_unset(cmd, &my_env);

    printf("\nAprès unset:\n");
    ft_print_array(my_env);

    // Nettoyage mémoire
    for (int i = 0; my_env[i]; i++)
        free(my_env[i]);
    free(my_env);

    return 0;
}

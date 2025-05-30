/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:32:04 by sradosav          #+#    #+#             */
/*   Updated: 2025/05/30 22:32:05 by sradosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void    ft_write_export(char *str)
{
    int i;

    write(1, "declare -x ", 11);
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
        write(1, "\"", 1);
    }    
    write(1, "\n", 1);
}

int is_valid_identifier(char *str)
{
    int i;

    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    i = 1;
    while ( str[i]) 
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
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

void    ft_export_vars(char **str, t_shell *shell)
{
    int i;
    int var_len;
    char    **var;

    i = 1;
    while (str[i])
    {
        if (!is_valid_identifier(str[i]))
        {
            printf("minishell: export: `%s': not a valid identifier\n", str[i]);
            shell->exit_status = 1;
        }
        else
        {
            var_len = 0;
            while (str[var_len] && str[var_len] != '=')
                var_len++;
            
        }
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
        update_or_add("_", str[str_size - 1], shell->env, 0);
        ft_print_export(shell);        
		shell->exit_status = 0;
    }
    else
    {
        shell->exit_status = 0;
        update_or_add("_", str[str_size - 1], shell->env, 0);
        ft_export_vars(str, shell);
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

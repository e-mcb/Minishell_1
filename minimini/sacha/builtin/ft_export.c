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

t_envvar	*copy_env_list(t_envvar *env)
{
	t_envvar	*copy;
	t_envvar	*tail;
	t_envvar	*new_node;

	copy = NULL;
	tail = NULL;
	while (env)
	{
		new_node = malloc(sizeof(t_envvar));
		if (!new_node)
		{
			//FT_EXIT
		}
		new_node->var = ft_strdup(env->var);
		if (!new_node->var)
		{
			//FT_EXIT
		}
		new_node->exported = env->exported;
		new_node->next = NULL;
		if (!copy)
			copy = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		env = env->next;
	}
	return (copy);
}

void	ft_sort_env_list(t_envvar *head)
{
	int			swapped;
	t_envvar	*ptr;
	char		*tmp;

	if (!head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next)
		{
			if (ft_strcmp(ptr->var, ptr->next->var) > 0)
			{
				tmp = ptr->var;
				ptr->var = ptr->next->var;
				ptr->next->var = tmp;
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
}

void	ft_write_export(char *str)
{
	int	i;

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
		while (str[i] != 0)
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

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_export(t_shell *shell)
{
	t_envvar	*env_copy;
	t_envvar	*iter;

	env_copy = copy_env_list(shell->env);
	ft_sort_env_list(env_copy);
	iter = env_copy;
	while (iter)
	{
		if (iter->exported == 1 && ft_strncmp(iter->var, "_=", 2) != 0)
			ft_write_export(iter->var);
		iter = iter->next;
	}
	free_list(&env_copy);
}

void	ft_export_vars(char **str, t_shell *shell)
{
	int		i;
	int		var_len;
	char	*var;
	char	*value;

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
			while (str[i][var_len] && str[i][var_len] != '=')
				var_len++;
			var = ft_strndup(str[i], var_len);
			if (!var)
			{
				//FT_EXIT
			}
			if (ft_strchr(str[i], '='))
				value = ft_strchr(str[i], '=') + 1;
			else
				value = NULL;
			update_or_add(var, value, shell, 1);
			free(var);
		}
		i++;
	}
}

// COMME POUR LES AUTRES FONCTIONS, TOUJOURS ENVOYER export EN PREMIERE LIGNE
// DU TABLEAU
void	ft_export(char **str, t_shell *shell)
{
	int	str_size;

	str_size = ft_strsize(str);
	if (!str[1])
	{
		update_or_add("_", str[str_size - 1], shell, 0);
		ft_print_export(shell);
		shell->exit_status = 0;
	}
	else
	{
		shell->exit_status = 0;
		update_or_add("_", str[str_size - 1], shell, 0);
		ft_export_vars(str, shell);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell		*shell;

// 	shell = malloc(sizeof(t_shell));
// 	if (!shell)
// 		return (1);
// 	shell->env = NULL;
// 	shell->exit_status = 0;
// 	char *test[] = {"export", "Hello=Zbbbbbooo", "world", NULL};
// 	// char *test[] = {"export", NULL};

// 	shell->env = ft_env_to_list(envp, shell);

// 	ft_export(test, shell);	

// 	ft_print_export(shell);

// 	free_list(&(shell->env));
// 	free(shell);

// 	return 0;
// }

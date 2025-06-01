/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:30:55 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/01 19:12:16 by sradosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	free_list(t_envvar **head)
{
	t_envvar	*current;
	t_envvar	*next;

	current = *head;
	while (current)
	{
		if (current->var)
		{
			free(current->var);
			current->var = NULL;
		}
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

t_envvar	*create_env_var(char *str, int exported)
{
	t_envvar	*node;

	node = malloc(sizeof(t_envvar));
	if (!node)
		return (NULL);
	node->var = ft_strdup(str);
	if (!node->var)
	{
		free(node);
		return (NULL);
	}
	node->exported = exported;
	node->next = NULL;
	return (node);
}

void	add_env_var(t_shell *shell, char *str, int exported)
{
	t_envvar	*new_node;
	t_envvar	*current;

	new_node = create_env_var(str, exported);
	if (!new_node)
	{
		// FT_EXIT
	}
	if (!shell->env)
	{
		shell->env = new_node;
		return ;
	}		
	current = shell->env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_envvar	*ft_env_to_list(char **envp, t_shell *shell)
{
	int			i;
	int			exported;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		exported = 1;
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			exported = 0;
		add_env_var(shell, envp[i], exported);
		i++;
	}
	return (shell->env);
}

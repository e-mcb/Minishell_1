/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:31:57 by sradosav          #+#    #+#             */
/*   Updated: 2025/06/01 16:22:01 by sradosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <ctype.h>

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (42);
	else
		return (0);
}

int	ft_is_number(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

// ON PASSE TOUS LES POINTEURS A FREE DANS T_SHELL
// DU COUP FONCTION A FAIRE QUI FREE TOUT EN MODE IF.... FREE...
void	ft_exit(char **str, t_shell *shell)
{
	int	exit_code;

	printf("exit\n");
	if (str[1] == NULL)
		exit_code = 0;
	else if (!ft_is_number(str[1]))
	{
		fprintf(stderr, "bash: exit: %s: numeric argument required\n", str[1]);
		exit_code = 2;
	}
	else if (str[2] != NULL)
	{
		ft_putstr_fd("bash: exit: trop d'arguments\n", 2);
		shell->exit_status = 1;
		return ;
	}
	else
		exit_code = (ft_atoi(str[1]) % 256);
	shell->exit_status = exit_code;
	free_list(&(shell->env));
	free(shell);
	exit(exit_code);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell		*shell;
// 	// char *cmd[] = {"exit", NULL};
// 	// char *cmd[] = {"exit", "zboob", "zbooby", NULL};
// 	// char *cmd[] = {"exit", "47", NULL};
// 	// char *cmd[] = {"exit", NULL};
// 	char *cmd[] = {"exit","260", NULL};

// 	shell = malloc(sizeof(t_shell));
// 	if (!shell)
// 		return (1);
// 	shell->env = NULL;
// 	shell->exit_status = 0;
// 	shell->env = ft_env_to_list(envp, shell);
// 	ft_exit(cmd, shell);
// 	free_list(&(shell->env));
// 	free(shell);
// 	return (0);
// }

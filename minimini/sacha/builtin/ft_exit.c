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

int ft_is_number(const char *str)
{
    if (*str == '+' || *str == '-')
        str++;
    if (*str == '\0')
        return 0;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}
// ON PASSE TOUS LES POINTEURS A FREE DANS T_SHELL
// DU COUP FONCTION A FAIRE QUI FREE TOUT EN MODE IF.... FREE...
int ft_exit(char **str, t_shell *shell)
{
    int exit_code;
    
    exit_code = 0;
    printf("exit\n");
    if (str[1] == NULL)
    {
        // FREE AVANT DE SORTIR
        shell->exit_status = 0;
        exit(0); 
    }
    else if (!is_number(str[1]))
    {
        // ARGUMENT NON NUMERIQUE - MESSAGE ET SORTIE 2
        fprintf(stderr, "bash: exit: %s: argument numérique nécessaire\n", str[1]);
        shell->exit_status = 2;
        exit(2);
    }
    else if (str[2] != NULL)
    {
        // TROP D ARGUMENTS, MESSAGE D ERREUR MAIS NE QUITTE PAS
        ft_putstr_fd("bash: exit: trop d'arguments\n", 2);
        shell->exit_status = 1;
        return 1;
    }
    else
    {
        // ARGUMENT NUMERIQUE ON QUITTE AVEC CE CODE
        exit_code = (ft_atoi(str[1]) % 256);
        shell->exit_status = exit_code;
        exit(exit_code);
    }
    return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:31:57 by sradosav          #+#    #+#             */
/*   Updated: 2025/05/30 22:31:58 by sradosav         ###   ########.fr       */
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

int ft_exit(char **args, char **env)
{
    int exit_code;
    
    exit_code = 0;
    printf("exit\n");
    if (args[1] == NULL)
    {
        // FREE AVANT DE SORTIR
        // METTRE LE CODE DE SORTIE A 0
        exit(0); 
    }
    else if (!is_number(args[1]))
    {
        // ARGUMENT NON NUMERIQUE - MESSAGE ET SORTIE 2
        fprintf(stderr, "bash: exit: %s: argument numérique nécessaire\n", args[1]);
        exit(2);
    }
    else if (args[2] != NULL)
    {
        // TROP D ARGUMENTS, MESSAGE D ERREUR MAIS NE QUITTE PAS
        ft_putstr_fd("bash: exit: trop d'arguments\n", 2);
        // METTRE LE CODE DE SORTIE A 1
        return 1;
    }
    else
    {
        // ARGUMENT NUMERIQUE ON QUITTE AVEC CE CODE
        exit_code = ft_atoi(args[1]) % 256;
        exit(exit_code);
    }
    return 0;
}

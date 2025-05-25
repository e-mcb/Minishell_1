#ifndef BUILTIN_H
# define BUILTIN_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


size_t	ft_strlen(const char *str);
int	    ft_strsize(char **str);
int	    ft_strcmp(char *s1, char *s2);
int	    ft_strncmp(char *s1, char *s2, unsigned int n);
int     array_len(char **str);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_strdup_array(char **src);
void	ft_print_array(char **str);
void	ft_putstr_fd(char *str, int fd);
void	update_env(char *var, char *str, char **env);

#endif
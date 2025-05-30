#ifndef BUILTIN_H
# define BUILTIN_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct s_envvar
{
	char		*var;
	int			exported;
	struct s_envvar	*next;
}	t_envvar;

typedef struct s_shell
{
	t_envvar	*env;
	int     exit_status;
}	t_shell;


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
// void	update_env(char *var, char *str, char **env);
// int		env_var_exists(char *var, char **env);
int		add_env_var(t_envvar **head, char *str, int exported);
void	update_or_add(char *var, char *str, t_envvar *env, int exported);
int		env_var_exists(char *var, t_envvar *env);
t_envvar	*ft_env_to_list(char **envp);
char	*ft_getenv(char *var, t_envvar *env);
char	*ft_strchr(char *s, int c);

#endif
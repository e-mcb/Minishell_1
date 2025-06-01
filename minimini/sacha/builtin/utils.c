/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:32:44 by sradosav          #+#    #+#             */
/*   Updated: 2025/05/30 22:32:45 by sradosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (42);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c < 'A') || (c > 'Z' && c < 'a') || (c > 'z'))
		return (0);
	else
		return (42);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	c_char;

	c_char = (char)c;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == c_char)
			return (s + i);
		i++;
	}
	if (s[i] == c_char)
		return (s + i);
	return (NULL);
}

int	ft_strsize(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	array_len(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		len += ft_strlen(str[i]);
		i++;
	}
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	while (s1[i] != 0)
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = 0;
	return (s3);
}

char	**ft_strdup_array(char **src)
{
	int		size;
	int		i;
	char	**dst;

	size = ft_strsize(src);
	dst = malloc(sizeof(char *) * (size + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			while (--i >= 0)
				free(dst[i]);
			free(dst);
			return (NULL);
		}
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*copy;

	i = 0;
	while (s[i] && i < n)
		i++;
	copy = (char *)malloc(sizeof(char) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}


void	ft_print_array(char **str)
{
	int	i;
	int	j;

	if (!str)
		return ;
	i = 0;
	j = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	return ;
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	env_var_exists(char *var, t_envvar *env)
{
	size_t		len;
	char		*var_equal;
	t_envvar	*copy_env;

	if (!var || !env)
		return (0);
	var_equal = ft_strjoin(var, "=");
	if (!var_equal)
		return (-1);
	len = ft_strlen(var);
	copy_env = env;
	while (copy_env)
	{
		if (ft_strcmp(copy_env->var, var) == 0)
		{
			free(var_equal);
			return (1);
		}
		if (ft_strncmp(copy_env->var, var_equal, len + 1) == 0)
		{
			free(var_equal);
			return (1);
		}
		copy_env = copy_env->next;
	}
	free(var_equal);
	return (0);
}

void	update_env(char *var, char *str, t_envvar *env)
{
	size_t		len;
	int			i;
	char		*full_var;
	char		*temp;
	t_envvar	*copy_env;

	i = 0;
	full_var = ft_strjoin(var, "=");
	len = ft_strlen(full_var);
	copy_env = env;
	while (copy_env)
	{
		if (ft_strncmp(copy_env->var, full_var, len) == 0)
		{
			free(copy_env->var);
			temp = ft_strjoin("=", str);
			copy_env->var = ft_strjoin(var, temp);
			free(temp);
			free(full_var);
			return ;
		}
		copy_env = copy_env->next;
	}
	free(full_var);
}

void	update_or_add(char *var, char *str, t_envvar *env, int	exported)
{
	char	*temp;
	char	*temp2;
	int		exists;

	exists = env_var_exists(var, env);
	if (exists == 1)
		update_env(var, str, env);
	else if (exists == -1)
		return ;
	else
	{
		temp = ft_strjoin(var, "=");
		if (!temp)
			return ;
		temp2 = ft_strjoin(temp, str);
		free(temp);
		if (!temp2)
			return ;
		add_env_var(&env, temp2, exported);
		free(temp2);
	}
	return ;
}

char *ft_getenv(char *var, t_envvar *env)
{
	size_t len;
	char *entry;
	t_envvar	*env_copy;

	if (!var)
		return NULL;
	len = ft_strlen(var);
	env_copy = env;
	while (env_copy)
	{
		entry = env_copy->var;
		if (ft_strncmp(entry, var, len) == 0 && entry[len] == '=')
			return entry + len + 1;
		env_copy = env_copy->next;
	}
	return NULL;
}

// int	env_var_exists(char *var, char **env)
// {
// 	size_t	len;
// 	int		i;
// 	char	*full_var;

// 	if (!var || !env)
// 		return (0);
// 	full_var = ft_strjoin(var, "=");
// 	if (!full_var)
// 		return (0);
// 	len = strlen(full_var);
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (strncmp(env[i], full_var, len) == 0)
// 		{
// 			free(full_var);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	free(full_var);
// 	return (0);
// }

// void	update_env(char *var, char *str, char **env)
// {
// 	size_t	len;
// 	int		i;
// 	char	*full_var;
// 	char	*temp;

// 	i = 0;
// 	full_var = ft_strjoin(var, "=");
// 	len = ft_strlen(full_var);
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], full_var, len) == 0)
// 		{
// 			free(env[i]);
// 			temp = ft_strjoin("=", str);
// 			env[i] = ft_strjoin(var, temp);
// 			free(temp);
// 			free(full_var);
// 			return ;
// 		}
// 		i++;
// 	}
// 	free(full_var);
// }

// char	**add_env_var(char *var, char *str, char **env)
// {
// 	int		len;
// 	char	**new_env;
// 	char	*new_var;
// 	int		i;
// 	char	*temp;

// 	len = ft_strsize(env);
// 	new_env = malloc(sizeof(char *) * (len + 2));
// 	if (!new_env)
// 		return (env);
// 	i = -1;
// 	while (++i < len)
// 		new_env[i] = env[i];
// 	new_var = NULL;
// 	temp = ft_strjoin("=", str);
// 	if (!temp)
// 		return (free(new_env), env);
// 	new_var = ft_strjoin(var, temp);
// 	free(temp);
// 	if (!new_var)
// 		return (free(new_env), env);
// 	new_env[len] = new_var;
// 	new_env[len + 1] = NULL;
// 	return (free(env), new_env);
// }

// void	update_or_add(char *var, char *str, char **env)
// {
// 	if (env_var_exists("_", env) == 1)
// 		update_env("_", str, env);
// 	else
// 		env = add_env_var("_", str, env);
// 	return ;
// }

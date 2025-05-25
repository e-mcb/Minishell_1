#include "builtin.h"

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

int	env_var_exists(char *var, char **env)
{
	size_t	len;
	int		i;
	char	*full_var;

	if (!var || !env)
		return (0);
	full_var = ft_strjoin(var, "=");
	if (!full_var)
		return (0);
	len = strlen(full_var);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], full_var, len) == 0)
		{
			free(full_var);
			return (1);
		}
		i++;
	}
	free(full_var);
	return (0);
}

void	update_env(char *var, char *str, char **env)
{
	size_t	len;
	int		i;
	char	*full_var;
	char	*temp;

	i = 0;
	full_var = ft_strjoin(var, "=");
	len = ft_strlen(full_var);
	while (env[i])
	{
		if (ft_strncmp(env[i], full_var, len) == 0)
		{
			free(env[i]);
			temp = ft_strjoin("=", str);
			env[i] = ft_strjoin(var, temp);
			free(temp);
			free(full_var);
			return ;
		}
		i++;
	}
	free(full_var);
}

char	**add_env_var(char *var, char *str, char **env)
{
	int		len;
	char	**new_env;
	char	*new_var;
	int		i;
	char	*temp;

	len = ft_strsize(env);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (env);
	i = -1;
	while (++i < len)
		new_env[i] = env[i];
	new_var = NULL;
	temp = ft_strjoin("=", str);
	if (!temp)
		return (free(new_env), env);
	new_var = ft_strjoin(var, temp);
	free(temp);
	if (!new_var)
		return (free(new_env), env);
	new_env[len] = new_var;
	new_env[len + 1] = NULL;
	return (free(env), new_env);
}

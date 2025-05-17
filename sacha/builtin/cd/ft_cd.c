#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int array_len(char **str)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(str[i])
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

int	ft_strsize(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

char *ft_getenv(char *var, char **env_copy)
{
    size_t len;
    int i = 0;
    char *entry;

    if (!var)
        return NULL;
    len = ft_strlen(var);
    while (env_copy[i])
    {
        entry = env_copy[i];
        if (ft_strncmp(entry, var, len) == 0 && entry[len] == '=')
            return entry + len + 1;
        i++;
    }
    return NULL;
}

void	update_env(char *var, char *str, char **env)
{
	size_t len;
    int i = 0;
    char *entry;
	char *temp;

    len = ft_strlen(str);
    while (env[i])
    {
        entry = env[i];
        if (ft_strncmp(entry, var, 2) == 0)
		{
            free(env[i]);
			env[i] = ft_strjoin(var, str);
			return ;
		}
        i++;
    }
}

int ft_cd(char **str, char **env)
{
    char *pwd;
    char    *current_directory;
    char cwd[1024];

    pwd = ft_getenv("PWD", env);
    if (!str[1]) {
        ft_putstr_fd("minishell: cd: missing argument (absolute or relative path required)\n", 2);
        update_env("_=", "cd", env);
        return 1;
    }
    if (str[2]) {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        update_env("_=", str[ft_strsize(str) - 1], env);
        return 1;
    }
    if (str[1][0] == '~' || (str[1][0] == '-' && str[1][1] == '\0')) {
        ft_putstr_fd("minishell: cd: only relative or absolute paths are supported\n", 2);
        update_env("_=", str[ft_strsize(str) - 1], env);
        return 1;
    }
    if (chdir(str[1]) != 0) {
        perror("minishell: cd");
        update_env("_=", str[ft_strsize(str) - 1], env);
        return 1;
    }
    update_env("_=", str[ft_strsize(str) - 1], env);
    update_env("OLDPWD=", pwd, env);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_env("PWD=", cwd, env);    
    ft_print_array(env);
    return 0;
}

int main(int argc, char **argv, char **envp)
{
    char cwd[1024];
    char **env;

    env = ft_strdup_array(envp);
    if (ft_cd(argv, env) != 0)
        return 1;

    // Affiche le répertoire courant après le cd
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("Current directory: %s\n", cwd);
    else
        perror("getcwd");
    

    return 0;
}
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

// _____________________________________________________________________________

// DEBUT DE LA FONCTION ECHO ICI, AU DESSUS C EST QUE DES UTILS QUE J AI RECOPIE
// _____________________________________________________________________________

void	update_env(char *str, char **env)
{
	size_t len;
    int i = 0;
    char *entry;
	char *temp;

    len = ft_strlen(str);
    while (env[i])
    {
        entry = env[i];
        if (ft_strncmp(entry, "_=", 2) == 0)
		{
            free(env[i]);
			temp = ft_strdup("_=");
			env[i] = ft_strjoin("_=", str);
			free(temp);
			//// ICI PREVOIR D ENVOYER T_SHELL A LA PLACE DE ENV ET DE FREE EN CAS D ERREUR DU DUP
			return ;
		}
        i++;
    }
}

// MAIN SI EXECUTABLE
// int	main(int argc, char *argv[])
// {
// 	int	start;
// 	int	newline;

// 	start = 1;
// 	newline = 1;
// 	if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
// 	{
// 		newline = 0;
// 		start = 2;
// 	}
// 	while (start < argc)
// 	{
// 		printf("%s", argv[start]);
// 		if (start < argc - 1)
// 			printf(" ");
// 		start++;
// 	}
// 	if (newline)
// 		printf("\n");
// 	return (0);
// }

int	is_n_flag(char *s)
{
	int	i = 0;

	if (!s || s[i++] != '-')
		return (0);
	while (s[i])
		if (s[i++] != 'n')
			return (0);
	return (1);
}

int	ft_echo(char **str, char **env)
{
	int	start = 0;
	int	newline = 1;
	int	len = array_len(str);

	while (str[start] && is_n_flag(str[start]))
	{
		newline = 0;
		start++;
    }
	while (str[start])
	{
		printf("%s", str[start]);
		if (str[start + 1])
			printf(" ");
		start++;
	}
	if (start > 0)
		update_env(str[start - 1], env);
	else
		update_env("echo", env);
	if (newline)
		printf("\n");
	ft_print_array(env);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
    char *test1[] = {"Hello", "world", NULL};
    char *test2[] = {"-n", "Hello", "world", NULL};
    char *test3[] = {"-n", "-n", "Hello", NULL};
    char *test4[] = {"-n", "-wrong", "Hello", NULL};
    char *test5[] = {NULL};
    char *test6[] = {"-nnnnnn", "-nnn", NULL};
	char **env;

	env = ft_strdup_array(envp);

    printf("Test 1:\n");
    ft_echo(test1, env); // => Hello world\n

    printf("Test 2:\n");
    ft_echo(test2, env); // => Hello world

    printf("Test 3:\n");
    ft_echo(test3, env); // => Hello

    printf("Test 4:\n");
    ft_echo(test4, env); // => -wrong Hello\n

    printf("Test 5:\n");
    ft_echo(test5, env); // => \n

    printf("Test 6:\n");
    ft_echo(test6, env); // => \n

    return 0;
}
#include <stdio.h>
#include <string.h>

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

int	ft_echo(char **str)
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
	if (newline)
		printf("\n");
	return (0);
}

int main(void)
{
    char *test1[] = {"Hello", "world", NULL};
    char *test2[] = {"-n", "Hello", "world", NULL};
    char *test3[] = {"-n", "-n", "Hello", NULL};
    char *test4[] = {"-n", "-wrong", "Hello", NULL};
    char *test5[] = {NULL};
    char *test6[] = {"-nnnnnn", "Hello", NULL};

    printf("Test 1:\n");
    ft_echo(test1); // => Hello world\n

    printf("Test 2:\n");
    ft_echo(test2); // => Hello world

    printf("Test 3:\n");
    ft_echo(test3); // => Hello

    printf("Test 4:\n");
    ft_echo(test4); // => -wrong Hello\n

    printf("Test 5:\n");
    ft_echo(test5); // => \n

    printf("Test 6:\n");
    ft_echo(test6); // => \n

    return 0;
}
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

int	ft_echo(char **str)
{
    int	start;
	int	newline;
    int len;

	start = 0;
	newline = 1;
    len = array_len(str);
    if (str)
    {
        if (str[start] && ft_strcmp(str[start], "-n") == 0)
        {
            newline = 0;
            start = 1;
        }
        while (str[start] && ft_strcmp(str[start], "-n") == 0)
            start++;
        while (str[start])
        {
            printf("%s", str[start]);
            if (start < len - 1)
                printf(" ");
            start++;
        }
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

    return 0;
}
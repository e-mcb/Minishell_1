#include <stdio.h>
#include <string.h>

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

int	main(int argc, char *argv[])
{
	int	start;
	int	newline;

	start = 1;
	newline = 1;
	if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		start = 2;
	}
	while (start < argc)
	{
		printf("%s", argv[start]);
		if (start < argc - 1)
			printf(" ");
		start++;
	}
	if (newline)
		printf("\n");
	return (0);
}

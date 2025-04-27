#ifndef TEST_H
# define TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>


char 	*strnstr(const char *haystack, const char *needle, size_t len);
int 	count_quotes (char *str);
char	**ft_split2(char const *s, char c);
size_t 	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
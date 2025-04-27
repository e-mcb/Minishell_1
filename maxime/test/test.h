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
# include <stdbool.h>

#define MAX_FD 1023

typedef enum e_token_type
{
	TOKEN_TYPE_WORD,
	TOKEN_TYPE_PIPE,
	TOKEN_TYPE_REDIRECT_IN,
	TOKEN_TYPE_REDIRECT_OUT,
	TOKEN_TYPE_APPEND,
	TOKEN_TYPE_HEREDOC,
	TOKEN_TYPE_SQUOTE,
	TOKEN_TYPE_DQUOTE,
	TOKEN_TYPE_FD,
} t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
} t_token;


char 	*strnstr(const char *haystack, const char *needle, size_t len);
int 	count_quotes (char *str);
char	**ft_split2(char const *s, char c);
size_t 	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int 	count_quotes (char *str);
bool	is_quote(char c);
bool	is_closing_quote(char c, char opening_quote);
bool	handle_quotes(char c, bool *in_quotes, char *opening_quote);
char 	*strnstr(const char *haystack, const char *needle, size_t len);
char *ft_strdup(char *str);
size_t ft_strlen(const char *str);
char *ft_substrword(char *str, int start, int end);


#endif
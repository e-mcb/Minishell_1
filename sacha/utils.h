#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

int		ft_strsize(char **str);
void	ft_free_str_array(char **str);
void	ft_print_array(char **str);
char	**ft_strdup_array(char **src);
int		ft_starts_or_ends_with_pipe(const char *str);
int		ft_isspace(char c);
int		ft_has_invalid_quotes(const char *str);
char	*ft_remove_wrapping_quotes(const char *str);

#endif

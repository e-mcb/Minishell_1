#include "test.h"

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	if (!dst || !src)
		return (0);
	src_len = strlen(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

int count_quotes (char *str)
{
	int i = 0;
	int flag_s = 0;
	int flag_d = 0;

	while (str[i])
	{
		if (str[i] == '\'' && flag_d == 0)
		{
			if (flag_s == 0)
				flag_s = 1;
			else
				flag_s = 0;
		}
		if (str[i] == '\"' && flag_s == 0)
		{
			if (flag_d == 0)
				flag_d = 1;
			else
				flag_d = 0;
		}
		i++;
	}
	return (flag_s + flag_d);
}

char *strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t needle_len;

	if (!*needle)
		return (char *)haystack;

	needle_len = strlen(needle);
	while (*haystack && len-- >= needle_len) {
		if (!strncmp(haystack, needle, needle_len))
			return (char *)haystack;
		haystack++;
	}
	return NULL;
}
#include "expand.h"

char *get_env_value(const char *name)
{
	char *value = getenv(name);
	if (!value)
		return strdup("");
	return strdup(value);
}

static void init_ex(t_expand *ex)
{
    ex->i = 0;
    ex->j = 0;
    ex->count = 0;
    ex->start = 0;
    ex->in_single_quote = 0;
    ex->in_double_quote = 0;
}

static void process_single_quote(const char *input, t_expand *ex)
{
    if (ex->i > ex->start)
        ex->result[ex->j++] = strndup_custom(input + ex->start, ex->i - ex->start);
    ex->in_single_quote = !ex->in_single_quote;
    ex->i++;
    ex->start = ex->i;
}

static void process_double_quote(const char *input, t_expand *ex)
{
    if (ex->i > ex->start)
        ex->result[ex->j++] = strndup_custom(input + ex->start, ex->i - ex->start);
    ex->in_double_quote = !ex->in_double_quote;
    ex->i++;
    ex->start = ex->i;
}

static void process_dollar(const char *input, char *varname, char *value, t_expand *ex)
{
    if (ex->i > ex->start)
        ex->result[ex->j++] = strndup_custom(input + ex->start, ex->i - ex->start);
    ex->i++;
    ex->start = ex->i;
    while (input[ex->i] && (ft_isalnum(input[ex->i]) || input[ex->i] == '_'))
        ex->i++;
    varname = strndup_custom(input + ex->start, ex->i - ex->start);
    value = get_env_value(varname);
    ex->result[ex->j++] = value;
    free(varname);
    ex->start = ex->i;
}

char **split_and_expand(const char *input)
{
    t_expand    ex;
    char    *varname;
    char    *value;

	init_ex(&ex);
    ex.result = malloc(sizeof(char *) * (ft_count_segments(input) + 1));
	if (!ex.result)
		return NULL;
	while (input[ex.i])
	{
		if (input[ex.i] == '\'' && !ex.in_double_quote)
            process_single_quote(input, &ex);
		else if (input[ex.i] == '"' && !ex.in_single_quote)
            process_double_quote(input, &ex);
		else if (input[ex.i] == '$' && !ex.in_single_quote)
            process_dollar(input, varname, value, &ex);
		else
            ex.i++;
	}
	if (ex.i > ex.start)
        ex.result[ex.j++] = strndup_custom(input + ex.start, ex.i - ex.start);
    ex.result[ex.j] = NULL;
	return (ex.result);
}
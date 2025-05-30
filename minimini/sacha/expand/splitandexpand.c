#include "expand.h"

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

static void process_dollar(const char *input, t_expand *ex)
{
    char    *value;

    if (ex->i > ex->start)
        ex->result[ex->j++] = strndup_custom(input + ex->start, ex->i - ex->start);
    if (input[ex->i + 1] == '$')
        case_double_dollar(ex);
    else if (input[ex->i + 1] == ' ' || input[ex->i + 1] == '\0')//WHITE SPACE ????
        case_only_dollar(ex);
    else if (input[ex->i + 1] == '?')
        case_question_mark(ex, value);
    else
        case_env_var(ex, value, input);   
}

char **split_and_expand(const char *input)
{
    t_expand    ex;

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
            process_dollar(input, &ex);
		else
            ex.i++;
	}
	if (ex.i > ex.start)
        ex.result[ex.j++] = strndup_custom(input + ex.start, ex.i - ex.start);
    ex.result[ex.j] = NULL;
	return (ex.result);
}
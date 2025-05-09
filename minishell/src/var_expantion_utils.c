#include "minishell.h"


int	handle_quoted_part(const char *input, int *i, char **expanded_str)
{
	char	*temp;

	temp = ft_substr(input, *i, 1);
	if (!temp)
		return (0);
	*expanded_str = ft_strjoin(*expanded_str, temp);
	free(temp);
	(*i)++;
	return (1);
}

int	handle_variable_expansion(const char *input, int *i, char **expanded_str)
{
	char	*temp;

	// Verifica se não está dentro de aspas simples
	if (input[*i + 1] != '\0' && input[*i + 1] != '\'' && input[*i + 1] != '\"')
	{
		temp = expand_variable(input, i);
		if (!temp)
			return (0);
		*expanded_str = ft_strjoin(*expanded_str, temp);
		free(temp);
	}
	return (1);
}




int	handle_normal_char(const char *input, int *i, char **expanded_str)
{
	char	*temp;

	temp = ft_substr(input, *i, 1);
	if (!temp)
		return (0);
	*expanded_str = ft_strjoin(*expanded_str, temp);
	free(temp);
	(*i)++;
	return (1);
}

char	*initialize_expanded_str(void)
{
	char	*expanded_str;

	expanded_str = ft_strdup("");
	if (!expanded_str)
		return (NULL);
	return (expanded_str);
}

int	handle_quotes_or_expansion(char **expanded_str, const char *input, int *i)
{
	if (inside_quotes(input, *i) == 1)
	{
		if (!handle_quoted_part(input, i, expanded_str))
			return (0);
	}
	else if (input[*i] == '$' && inside_quotes(input, *i) != 1)
	{
		if (!handle_variable_expansion(input, i, expanded_str))
			return (0);
	}
	else
	{
		if (!handle_normal_char(input, i, expanded_str))
			return (0);
	}
	return (1);
}

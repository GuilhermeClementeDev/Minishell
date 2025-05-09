#include "minishell.h"

int	inside_quotes(const char *str, int i)
{
	int	inside_single_quote;
	int	inside_double_quote;
	int	j;

	inside_single_quote = 0;
	inside_double_quote = 0;
	j = 0;
	while (j < i)
	{
		if (str[j] == '\'' && inside_double_quote % 2 == 0)  // Alteração para verificar aspas simples externas
			inside_single_quote = !inside_single_quote;
		else if (str[j] == '\"' && inside_single_quote % 2 == 0)  // Alteração para verificar aspas duplas externas
			inside_double_quote = !inside_double_quote;
		j++;
	}
	if (inside_single_quote)
		return (1); // Dentro de aspas simples
	if (inside_double_quote)
		return (2); // Dentro de aspas duplas
	return (0);  // Fora de aspas
}





int	is_delimiter(char c)
{
	if(ft_strchr(" \t\n\v\f\r", c) != NULL)
		return (1);
	return (0);
}

int	is_double_operator(const char *str, int i)
{
	if (str[i] == '|' && str[i + 1] == '|')
	{
		ft_putstr_fd("Syntax error: unexpected token '|'\n", 2);
		return (1);
	}
	if (str[i] == '&' && str[i + 1] == '&')
	{
		ft_putstr_fd("Syntax error: unexpected token '&'\n", 2);
		return (1);
	}
	return (0);
}

int	is_pipe_space_pipe(const char *str, int *i)
{
	if (str[*i] == '|' && is_delimiter(str[*i + 1]))
	{
		(*i)++;
		while (is_delimiter(str[*i]))
			(*i)++;
		if (str[*i] == '|')
		{
			ft_putstr_fd("Syntax error: unexpected token '|'\n", 2);
			return (1);
		}
		(*i)--;
	}
	return (0);
}

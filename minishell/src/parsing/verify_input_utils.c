/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:41:12 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/14 13:47:14 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (str[j] == '\'' && inside_double_quote % 2 == 0)
			inside_single_quote = !inside_single_quote;
		else if (str[j] == '\"' && inside_single_quote % 2 == 0)
			inside_double_quote = !inside_double_quote;
		j++;
	}
	if (inside_single_quote)
		return (1);
	if (inside_double_quote)
		return (2);
	return (0);
}

int	is_delimiter(char c)
{
	if (ft_strchr(" \t\n\v\f\r", c) != NULL)
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

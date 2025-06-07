/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:37:45 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/14 13:47:08 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_quotes(const char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quotes % 2 == 0)
			single_quotes++;
		else if (str[i] == '\"' && single_quotes % 2 == 0)
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (1);
	return (0);
}

//essa função ta erradaaaa "teste >  > outr_teste"
int	verify_redirects(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (inside_quotes(str, i))
		{
			i++;
			continue ;
		}
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == str[i])
				i++;
			i++;
			while (str[i] && is_delimiter(str[i]))
				i++;
			if (!str[i] || str[i] == '>' || str[i] == '<' || str[i] == '|')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	verify_double_tokens(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!inside_quotes(str, i))
		{
			if (is_double_operator(str, i))
				return (1);
			if (is_pipe_space_pipe(str, &i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	verify_tokens(const char *str)
{
	if (ft_strchr(str, '|') && str[0] == '|')
	{
		ft_putstr_fd("Syntax error: unexpected token '|'\n", 2);
		return (1);
	}
	if (ft_strchr(str, '|') && str[ft_strlen(str) - 1] == '|')
	{
		ft_putstr_fd("Syntax error: unexpected token '|'\n", 2);
		return (1);
	}
	if (ft_strchr(str, '&') && str[0] == '&')
	{
		ft_putstr_fd("Syntax error: unexpected token '&'\n", 2);
		return (1);
	}
	return (0);
}

int	check_syntax_error(const char *str)
{
	if (verify_quotes(str))
	{
		ft_putstr_fd("Syntax error: unclosed quotes\n", 2);
		return (1);
	}
	if (verify_redirects(str))
	{
		ft_putstr_fd("Syntax error: invalid redirection\n", 2);
		return (1);
	}
	if (verify_double_tokens(str))
		return (1);
	if (verify_tokens(str))
		return (1);
	return (0);
}

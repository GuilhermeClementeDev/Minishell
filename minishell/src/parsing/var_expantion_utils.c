/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expantion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:10:29 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/14 14:57:09 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quoted_part(const char *input, int *i, char **expanded_str)
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

int	var_expansion(const char *input, int *i, char **expanded_str)
{
	char	*temp;

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

int	quotes_or_expansion(char **exp_str, const char *input, int *i)
{
	if (inside_quotes(input, *i) == 1)
	{
		if (!quoted_part(input, i, exp_str))
			return (0);
	}
	else if (input[*i] == '$' && inside_quotes(input, *i) != 1)
	{
		if (!var_expansion(input, i, exp_str))
			return (0);
	}
	else
	{
		if (!handle_normal_char(input, i, exp_str))
			return (0);
	}
	return (1);
}

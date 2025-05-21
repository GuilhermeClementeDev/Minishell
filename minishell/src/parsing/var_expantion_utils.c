/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expantion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:10:29 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/15 18:43:35 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	concat_and_free_old(char **dest, char *src)
{
	char	*tmp;

	tmp = ft_strjoin(*dest, src);
	if (!tmp)
		return (0);
	free(*dest);
	*dest = tmp;
	return (1);
}

int	quoted_part(char *input, int *i, char **expanded_str)
{
	char	*temp;

	temp = ft_substr(input, *i, 1);
	if (!temp)
		return (0);
	if (!concat_and_free_old(expanded_str, temp))
	{
		free(temp);
		return (0);
	}
	free(temp);
	(*i)++;
	return (1);
}

int	var_expansion(char *input, int *i, char **expanded_str)
{
	char	*temp;

	if (input[*i + 1] != '\0' && input[*i + 1] != '\'' && input[*i + 1] != '\"')
	{
		temp = expand_variable(input, i);
		if (!temp)
			return (0);
		if (!concat_and_free_old(expanded_str, temp))
		{
			free(temp);
			return (0);
		}
		free(temp);
	}
	return (1);
}

int	handle_normal_char(char *input, int *i, char **expanded_str)
{
	char	*temp;

	temp = ft_substr(input, *i, 1);
	if (!temp)
		return (0);
	if (!concat_and_free_old(expanded_str, temp))
	{
		free(temp);
		return (0);
	}
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

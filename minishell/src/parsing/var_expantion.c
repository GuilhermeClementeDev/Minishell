/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expantion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:55:53 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/27 15:04:23 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var_name(char *str, int *i)
{
	int	begin;
	int	size;

	size = 0;
	begin = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		(*i)++;
		size++;
	}
	return (ft_substr(str, begin, size));
}
static char	*ft_domain_expansion(char *input, int *i, char *result, t_shell *shell)
{
	char	*name;
	char	*value;

	if (input[*i + 1] == '?')
	{
		(*i) += 2;
		value = ft_itoa(shell->status);
		result = ft_join_gnl(result, value);
		free(value);
	}
	else
	{
		(*i)++;
		name = get_var_name(input, i);
		if (!name)
			return (result);
		value = ft_strdup(get_env_value(shell->env, name));
		free(name);
		if (!value)
			return (result);
		result = ft_join_gnl(result, value);
		free(value);
	}
	return (result);
}
static char	*ft_add_one(char *input, int *i, char *result)
{
	char	tmp[2];

	tmp[0] = input[*i];
	tmp[1] = '\0';
	result = ft_join_gnl(result, tmp);
	(*i)++;
	return (result);
}

static char	*expand_variables(char *input, t_shell *shell)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*result;

	i = 0;
	in_single = 0;
	in_double = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single, i++;
		else if (input[i] == '\"' && !in_single)
			in_double = !in_double, i++;
		else if (input[i] == '$' && !in_single && input[i + 1])
			result = ft_domain_expansion(input, &i, result, shell);
		else
			result = ft_add_one(input, &i, result);
	}
	return (result);
}

void	expand_variables_in_token(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			expanded = expand_variables(tmp->value, shell);
			free(tmp->value);
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}
}

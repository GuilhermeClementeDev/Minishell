/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expantion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:55:53 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/14 14:58:32 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_var_value(const char *var)
{
	char	*value;

	value = getenv(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_variable(const char *input, int *index)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *index;
	(*index)++;
	while (input[*index] && (isalnum(input[*index]) || input[*index] == '_'))
		(*index)++;
	var_name = ft_substr(input, start + 1, *index - start - 1);
	var_value = get_env_var_value(var_name);
	free(var_name);
	return (var_value);
}

void	expand_variables_in_str(char **str, const char *input)
{
	int		i;
	char	*expanded_str;

	i = 0;
	expanded_str = ft_strdup("");
	while (input[i])
	{
		if (inside_quotes(input, i) == 1)
		{
			if (!quoted_part(input, &i, &expanded_str))
				return ;
		}
		else if (input[i] == '$' && inside_quotes(input, i) != 1)
		{
			if (!var_expansion(input, &i, &expanded_str))
				return ;
		}
		else
		{
			if (!handle_normal_char(input, &i, &expanded_str))
				return ;
		}
	}
	*str = expanded_str;
}

void	handle_expansion(t_token *token)
{
	char	*expanded_value;

	expanded_value = NULL;
	if (token->type == T_WORD)
	{
		if (!inside_quotes(token->value, 0))
		{
			expand_variables_in_str(&expanded_value, token->value);
			free(token->value);
			token->value = expanded_value;
		}
	}
}

void	expand_variables_in_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		handle_expansion(current);
		current = current->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expantion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:55:53 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/26 19:31:18 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_var_value(char *var)
{
	char	*value;

	value = getenv(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_variable(char *input, int *index)
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

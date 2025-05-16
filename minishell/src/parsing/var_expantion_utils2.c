/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expantion_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:20:18 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/15 18:42:29 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_variables_in_str_handle_error(char **expanded_str)
{
	if (*expanded_str)
	{
		free(*expanded_str);
		*expanded_str = NULL;
	}
}

static int	handle_expansion_case(int case_type, char *input, int *i,
				char **expanded_str)
{
	if (case_type == 1)
		return (quoted_part(input, i, expanded_str));
	if (case_type == 2)
		return (var_expansion(input, i, expanded_str));
	return (handle_normal_char(input, i, expanded_str));
}

static int	expand_variables_in_str_loop(char **exp_str, char *input)
{
	int	i;
	int	case_type;

	i = 0;
	while (input[i])
	{
		case_type = 0;
		if (inside_quotes(input, i) == 1)
			case_type = 1;
		else if (input[i] == '$' && inside_quotes(input, i) != 1)
			case_type = 2;
		if (case_type && !handle_expansion_case(case_type, \
			input, &i, exp_str))
		{
			expand_variables_in_str_handle_error(exp_str);
			return (0);
		}
		else if (!case_type && !handle_normal_char(input, &i, exp_str))
		{
			expand_variables_in_str_handle_error(exp_str);
			return (0);
		}
	}
	return (1);
}

void	expand_variables_in_str(char **str, char *input)
{
	char	*expanded_str;

	expanded_str = ft_strdup("");
	if (!expanded_str)
		return ;
	if (!expand_variables_in_str_loop(&expanded_str, input))
		return ;
	*str = expanded_str;
}

int	quotes_or_expansion(char **exp_str, char *input, int *i)
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

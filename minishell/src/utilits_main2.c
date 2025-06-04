/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_main2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:57:21 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/04 02:39:52 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space_or_invalid(char *input)
{
	if (!ft_not_only_spaces(input))
	{
		free(input);
		input = NULL;
		return (1);
	}
	if (check_syntax_error(input))
	{
		free(input);
		input = NULL;
		return (1);
	}
	return (0);
}

t_token	*list_token(char *input, t_shell *shell)
{
	t_token	*token_list;

	token_list = lexer(input);
	expand_variables_in_token(token_list, shell);
	return (token_list);
}

void	free_input_token_cmd(char *input, t_cmd *cmd_list)
{
	if (input)
		free(input);
	if (cmd_list)
		free_commands(cmd_list);
}

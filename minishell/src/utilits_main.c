/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:46:09 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/21 16:14:20 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_build_shell(t_shell *shell, char **envp)
{
	shell->env = alloc_env(count_env(envp));
	copy_env_skip(envp, shell->env, NULL, NULL);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
}

void	ft_clean_shell(t_shell *shell)
{
	free_input_token_cmd(shell->input, shell->cmds);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
}

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

t_token	*list_token(char *input)
{
	t_token	*token_list;

	token_list = lexer(input);
	expand_variables_in_token(token_list);
	clean_tokens(token_list);
	return (token_list);
}

void	free_input_token_cmd(char *input, t_cmd *cmd_list)
{
	free(input);
	free_commands(cmd_list);
}

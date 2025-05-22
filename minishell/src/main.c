/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/22 16:40:43 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_and_parse(t_shell *shell)
{
	shell->tokens = list_token(shell->input);
	shell->cmds = parse_tokens(shell->tokens);
	print_cmds(&shell->cmds);
	free_token_list(shell->tokens);
}
/*
int	execution(t_shell *shell)
{
	process_heredocs(shell->cmds);
	if (!prepare_execution(shell->cmds))
	{
		ft_clean_shell(shell);
		return (0);
	}
	execute_pipeline(shell->cmds, &shell->env);
	close_cmd_fds(shell->cmds);
	return (1);
}*/

static int	should_add_to_history(char *str)
{
	if (!str || !*str)
		return (0);
	if (str[0] == ' ' || (str[0] >= '\t' && str[0] <= '\r'))
		return (0);
	return (ft_not_only_spaces(str));
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	(void)argc;
	(void)argv;
	ft_build_shell(shell, envp);
	while (TRUE)
	{
		ft_signals();
		shell->input = readline("minishell> ");
		if (!shell->input)
			ft_exit(shell);
		if (is_space_or_invalid(shell->input))
			continue ;
		shell->tokens = list_token(shell->input);
		shell->cmds = parse_tokens(shell->tokens);
		if (should_add_to_history(shell->input))
			add_history(shell->input);
		ft_executer(shell);
		ft_clean_shell(shell);
	}
	free_env(shell->env);
	free(shell);
	clear_history();
	return (0);
}

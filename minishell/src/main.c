/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/02 18:14:06 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_and_parse(t_shell *shell)
{
	shell->tokens = list_token(shell->input, shell);
	shell->cmds = parse_tokens(shell->tokens);
	print_cmds(&shell->cmds);
	free_token_list(shell->tokens);
}

void	close_cmd_fds(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
}

static int	should_add_to_history(char *str)
{
	if (!str || !*str)
		return (0);
	if (str[0] == ' ' || (str[0] >= '\t' && str[0] <= '\r'))
		return (0);
	return (ft_not_only_spaces(str));
}

static void	handle_input_main(t_shell *shell)
{
	if (should_add_to_history(shell->input))
		add_history(shell->input);
	token_and_parse(shell);
	process_heredocs(shell->cmds);
	if (!prepare_execution(shell->cmds))
	{
		ft_clean_shell(shell);
		return ;
	}
	ft_executer(shell);
	close_cmd_fds(shell->cmds);
	ft_clean_shell(shell);
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
			ft_exit(shell, NULL);
		if (is_space_or_invalid(shell->input))
			continue ;
		handle_input_main(shell);
	}
	free_env(shell->env);
	free(shell);
	clear_history();
	return (0);
}

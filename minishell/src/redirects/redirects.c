/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:39:19 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/21 15:34:54 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Aplica os redirecionamentos, ajustando fds para cada comando
int	apply_redirects_to_fds(t_cmd *cmd)
{
	t_redirect	*redir;
	int			fd;
	int			error;

	error = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	redir = cmd->redirects;
	while (redir)
	{
		fd = 0;
		if (open_fd_redir(redir, &fd) == -1)
		{
			redir = redir->next;
			continue ;
		}
		verify_fd_cmd (cmd, redir, fd, &error);
		redir = redir->next;
	}
	cmd->redirect_error = error;
	return (error);
}

int	apply_redirects_to_all(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		ret;

	ret = 0;
	cmd = cmd_list;
	while (cmd)
	{
		if (apply_redirects_to_fds(cmd))
			ret = -1;
		cmd = cmd->next;
	}
	return (ret);
}

int	prepare_execution(t_cmd *cmd_list)
{
	if (apply_redirects_to_all(cmd_list) == -1)
	{
		ft_putstr_fd("Error: failed to apply redirects\n", 2);
		return (0);
	}
	if (setup_pipes(cmd_list) == -1)
	{
		ft_putstr_fd("Error: failed to create pipes\n", 2);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:39:19 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/29 22:32:17 by bieldojt         ###   ########.fr       */
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
	cmd->filename_error = NULL;
	redir = cmd->redirects;
	while (redir)
	{
		fd = open_fd_redir(redir);
		if (fd  == -1)
		{
			if(error == 0)
				cmd->filename_error = redir->filename;
			redir = redir->next;
			error = 1;
			continue ;
		}
		verify_fd_cmd(cmd, redir, fd);
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
	apply_redirects_to_all(cmd_list);
	setup_pipes(cmd_list);
	return (1);
}

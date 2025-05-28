/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:15:42 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/28 15:35:46 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_cmd_fd(t_cmd *cmd, t_redirect *redir, int fd)
{
	if (redir->type == T_RED_IN || redir->type == T_HEREDOC)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		cmd->fd_in = fd;
	}
	else
	{
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd->fd_out = fd;
	}
}

int	open_fd_redir(t_redirect *redir)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (redir->type == T_RED_IN)
		tmp_fd = open(redir->filename, O_RDONLY);
	else if (redir->type == T_RED_OUT)
		tmp_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == T_APPEND)
		tmp_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == T_HEREDOC)
		tmp_fd = open(redir->filename, O_RDONLY);
	return (tmp_fd);
}

int	verify_fd_cmd(t_cmd *cmd, t_redirect *r, int fd)
{
	if (fd < 0)
	{
		perror(r->filename);
		return (-1);
	}
	else
	{
		change_cmd_fd(cmd, r, fd);
		return (0);
	}
}

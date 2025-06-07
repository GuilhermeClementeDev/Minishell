/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:31:43 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/21 15:31:44 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_pipes(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		pipefd[2];

	cmd = cmd_list;
	while (cmd && cmd->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return (-1);
		}
		if (cmd->fd_out == STDOUT_FILENO)
			cmd->fd_out = pipefd[1];
		else
			close(pipefd[1]);
		if (cmd->next->fd_in == STDIN_FILENO)
			cmd->next->fd_in = pipefd[0];
		else
			close(pipefd[0]);
		cmd = cmd->next;
	}
	return (0);
}

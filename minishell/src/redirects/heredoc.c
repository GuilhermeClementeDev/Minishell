/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:31:31 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/21 15:31:36 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_heredoc_redirect(t_redirect *redir)
{
	char	*tmp_file;

	tmp_file = create_heredoc_file(redir->filename);
	if (!tmp_file)
		return (0);
	if (redir->filename)
		free(redir->filename);
	redir->filename = tmp_file;
	return (1);
}

void	process_heredocs(t_cmd *cmd_list)
{
	t_cmd		*cmd;
	t_redirect	*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				if (!handle_heredoc_redirect(redir))
				{
					cmd->redirect_error = 1;
					return ;
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

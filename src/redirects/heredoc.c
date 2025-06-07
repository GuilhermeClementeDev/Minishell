/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:31:31 by bieldojt          #+#    #+#             */
/*   Updated: 2025/06/02 18:17:21 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_heredoc_redirect(t_redirect *redir, int *count_heredocs)
{
	char	*tmp_file;

	tmp_file = create_heredoc_file(redir->filename, count_heredocs);
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
	int			count_heredocs;

	cmd = cmd_list;
	count_heredocs = 1;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				if (!handle_heredoc_redirect(redir, &count_heredocs))
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

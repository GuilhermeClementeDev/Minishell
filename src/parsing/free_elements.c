/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:23:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/18 00:33:28 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_redirects(t_redirect *redirects)
{
	t_redirect	*tmp;

	while (redirects)
	{
		tmp = redirects->next;
		if (redirects->type == T_HEREDOC)
			unlink(redirects->filename);
		free(redirects->filename);
		free(redirects);
		redirects = tmp;
	}
}

void	free_commands(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->args)
		{
			i = 0;
			while (cmds->args[i])
			{
				free(cmds->args[i]);
				i++;
			}
			free(cmds->args);
		}
		free_redirects(cmds->redirects);
		free(cmds);
		cmds = tmp;
	}
}

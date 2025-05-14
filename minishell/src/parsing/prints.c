/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:00:25 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/14 15:03:14 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		printf("[%s: %s]\n", token_type_to_str(tmp->type), tmp->value);
		tmp = tmp->next;
	}
}

void	print_cmds(t_cmd **cmd)
{
	int			i;
	t_cmd		*cmds;
	t_redirect	*redir;

	cmds = *cmd;
	while (cmds)
	{
		printf("Command:\n");
		i = 0;
		while (cmds->args && cmds->args[i])
		{
			printf("  argv[%d]: %s\n", i, cmds->args[i]);
			i++;
		}
		if (!cmds->args || i == 0)
			printf("  (empty argv)\n");
		redir = cmds->redirects;
		while (redir)
		{
			printf("  redirect: %s %s\n", redir_type_to_str(redir->type), \
			redir->filename);
			redir = redir->next;
		}
		cmds = cmds->next;
	}
}

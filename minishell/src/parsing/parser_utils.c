/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:01:13 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/14 13:47:53 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirect(t_token **token, t_redirect **redirects)
{
	t_redirect	*new;
	t_redirect	*curr;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (0);
	new->type = (*token)->type;
	new->next = NULL;
	if ((*token)->next && (*token)->next->type == T_WORD)
	{
		new->filename = ft_strdup((*token)->next->value);
		if (*redirects == NULL)
			*redirects = new;
		else
		{
			curr = *redirects;
			while (curr->next)
				curr = curr->next;
			curr->next = new;
		}
		*token = (*token)->next;
	}
	return (1);
}

int	is_redirect_type(int type)
{
	return (type == T_RED_IN || type == T_RED_OUT
		|| type == T_HEREDOC || type == T_APPEND);
}

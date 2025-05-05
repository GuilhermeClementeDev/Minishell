/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:56:51 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/04 23:27:08 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type == T_RED_IN || token->type == T_RED_OUT
			|| token->type == T_HEREDOC || token->type == T_APPEND)
		{
			// Pula o nome do arquivo
			if (token->next)
				token = token->next;
		}
		else if (token->type == T_WORD)
			count++;
		token = token->next;
	}
	return (count);
}




static char	**fill_args(t_token **token, t_redirect **redirects)
{
	char	**argv;
	int		count;
	int		i;

	count = count_args(*token);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*token && (*token)->type != T_PIPE)
	{
		if (is_redirect_type((*token)->type))
		{
			if (!handle_redirect(token, redirects))
				return (NULL);
		}
		else if ((*token)->type == T_WORD)
			argv[i++] = ft_strdup((*token)->value);
		*token = (*token)->next;
	}
	argv[i] = NULL;
	return (argv);
}



t_cmd	*parse_tokens(t_token *token)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new;
	t_token	*tmp;

	head = NULL;
	current = NULL;
	tmp = token;
	while (tmp)
	{
		new = malloc(sizeof(t_cmd));
		if (!new)
			return (NULL);
		new->redirects = NULL;
		new->args = fill_args(&tmp, &new->redirects);
		new->next = NULL;
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		if (tmp && tmp->type == T_PIPE)
			tmp = tmp->next;
	}
	return (head);
}



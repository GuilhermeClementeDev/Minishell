/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:24:19 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/09 16:40:48 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//LEMBRAR DE MUDAR O HEADER DA 42!!!!!!

#include "minishell.h"

t_token	*create_token(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

void	create_and_add_token(t_token **head, int type, char *value)
{
	t_token	*new_token;

	new_token = create_token(type, value);
	if (!new_token)
		return ;
	add_token(head, new_token);
}

t_token	*lexer(const char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (is_delimiter(input[i]))
			i++;
		else
			process_token(&head, input, &i);
	}
	return (head);
}

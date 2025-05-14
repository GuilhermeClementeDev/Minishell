/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:46:54 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/14 17:44:18 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_quoted(const char *input, int *i)
{
	int		len;
	char	quote;

	len = 0;
	quote = input[*i];
	(*i)++;
	len++;
	while (input[*i] && input[*i] != quote)
	{
		(*i)++;
		len++;
	}
	if (input[*i] == quote)
	{
		(*i)++;
		len++;
	}
	return (len);
}

static int	calc_word_len(const char *input, int *i)
{
	int	len;

	len = 0;
	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '"')
			len += skip_quoted(input, i);
		else if (is_delimiter(input[*i]) || input[*i] == '|' || \
		input[*i] == '<' || input[*i] == '>')
		{
			break ;
		}
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}

void	get_word(t_token **head, const char *input, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	len = calc_word_len(input, i);
	word = ft_substr(input, start, len);
	if (!word)
		return ;
	create_and_add_token(head, T_WORD, word);
}

static char	*remove_quotes(const char *str)
{
	int		i;
	int		j;
	char	*new;
	char	quote;

	new = malloc(ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				new[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

void	clean_tokens(t_token *head)
{
	char	*cleaned;

	while (head)
	{
		if (head->type == T_WORD)
		{
			cleaned = remove_quotes(head->value);
			free(head->value);
			head->value = cleaned;
		}
		head = head->next;
	}
}

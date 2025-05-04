/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/04 18:57:17 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*token_type_to_str(int type)
{
	if (type == T_WORD)
		return ("WORD");
	else if (type == T_PIPE)
		return ("PIPE");
	else if (type == T_REDIRECT_IN)
		return ("REDIR_IN");
	else if (type == T_REDIRECT_OUT)
		return ("REDIR_OUT");
	else if (type == T_HEREDOC)
		return ("HEREDOC");
	else if (type == T_APPEND)
		return ("APPEND");
	return ("UNKNOWN");
}

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

static int	should_add_to_history(char *str)
{
	if (!str || !*str)
		return (0);
	if (str[0] == ' ' || (str[0] >= '\t' && str[0] <= '\r'))
		return (0);
	return (ft_not_only_spaces(str));
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*token_list;

	(void)argc;
	(void)argv;
	(void)envp;
	while (TRUE)
	{
		input = readline("minishell> ");
		//input = "texte >  > outro_teste";
		if (!input)
			break ;
		//função que verifica se a string é vazia ou só tem espaços
		if (!ft_not_only_spaces(input))
		{
			free(input);
			continue ;
		}
		//função que verifica se a string tem aspas não fechadas
		if(check_syntax_error(input))
		{
			free(input);
			break ;
		}
		token_list = lexer(input); //se pa trata erro aqui de malloc???
		clean_tokens(token_list);
		print_tokens(&token_list);
		//free_token_list(token_list); //função que libera a lista de tokens
		if (should_add_to_history(input))
			add_history(input);
		//printf("%s\n", input);
		free(input);
	}
	clear_history();
	return (0);
}

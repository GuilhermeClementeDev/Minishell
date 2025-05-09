/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/09 11:31:12 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*token_type_to_str(int type)
{
	if (type == T_WORD)
		return ("WORD");
	else if (type == T_PIPE)
		return ("PIPE");
	else if (type == T_RED_IN)
		return ("REDIR_IN");
	else if (type == T_RED_OUT)
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


static const char	*redir_type_to_str(int type)
{
	if (type == T_RED_IN)
		return ("<");
	else if (type == T_RED_OUT)
		return (">");
	else if (type == T_HEREDOC)
		return ("<<");
	else if (type == T_APPEND)
		return (">>");
	return ("UNKNOWN");
}

void	print_cmds(t_cmd **cmd)
{
	int	i;
	t_cmd	*cmds;
	cmds = *cmd;
	t_redirect *redir;

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
			printf("  redirect: %s %s\n", redir_type_to_str(redir->type), redir->filename);
			redir = redir->next;
		}
		cmds = cmds->next;
	}
}

void	print_cmdsss(t_cmd **cmd)
{
	int	i;
	t_cmd	*cmds;
	cmds = *cmd;
	t_redirect *redir;

	while (cmds)
	{
		printf("Command:\n");
		i = 0;
		while (cmds->args && cmds->args[i])
		{
			printf("%s", cmds->args[i]);
			i++;
		}
			printf("\n");
		if (!cmds->args || i == 0)
			printf("  (empty argv)\n");
		redir = cmds->redirects;
		while (redir)
		{
			printf("  redirect: %s %s\n", redir_type_to_str(redir->type), redir->filename);
			redir = redir->next;
		}
		cmds = cmds->next;
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
	t_cmd	*cmd_list;

	(void)argc;
	(void)argv;
	(void)envp;
	while (TRUE)
	{
		input = readline("minishell> ");
		//input = ft_strdup("this is a test");
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
		//tokenização
		token_list = lexer(input);
		expand_variables_in_token(token_list); // Expande variáveis nos tokens
		clean_tokens(token_list);
		//print_tokens(&token_list); //função que imprime a lista de tokens



		//parsing
		cmd_list = parse_tokens(token_list); //se pa trata erro aqui de malloc???

		print_cmds(&cmd_list); //função que imprime a lista de comandos
		print_cmdsss(&cmd_list); //sadfgkhasgda

		if (should_add_to_history(input))
			add_history(input);
		//printf("%s\n", input);
		free(input);
		free_token_list(token_list);
		free_commands(cmd_list);
		input = NULL;
	}
	clear_history();
	return (0);
}

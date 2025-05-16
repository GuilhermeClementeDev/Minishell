/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:36 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/16 15:54:07 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*list_token(char *input)
{
	t_token	*token_list;

	token_list = lexer(input);
	expand_variables_in_token(token_list);
	clean_tokens(token_list);
	return (token_list);
}

void	free_input_token_cmd(char *input ,t_cmd *cmd_list)
{
	free(input);
	//free_token_list(token_list);
	free_commands(cmd_list);
}

int	is_space_or_invalid(char *input)
{
	if (!ft_not_only_spaces(input))
	{
		free(input);
		return (1);
	}
	if (check_syntax_error(input))
	{
		free(input);
		return (1);
	}
	return (0);
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
		//input = "cat << EOF > b";
		if (!input)
			break ;
		if (is_space_or_invalid(input))
			continue ;
		token_list = list_token(input);
		cmd_list = parse_tokens(token_list);
		free_token_list(token_list);
		print_cmds(&cmd_list);
		process_heredocs(cmd_list);
		if (apply_redirects_to_all(cmd_list) == -1)
		{
			ft_putstr_fd("Error: failed to apply redirects\n", 2);
			free_input_token_cmd(input, cmd_list);
			input = NULL;
			continue ;
		}
		execute_pipeline(cmd_list, &envp);
		close_cmd_fds(cmd_list);
		if (should_add_to_history(input))
			add_history(input);

		free_input_token_cmd(input, cmd_list);
		input = NULL;
	}
	clear_history();
	return (0);
}

#include "minishell.h"

int	is_append_or_output(t_token **head, const char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		create_and_add_token(head, T_APPEND, ">>");
		*i += 2;
		return (1);
	}
	else if (input[*i] == '>')
	{
		create_and_add_token(head, T_REDIRECT_OUT, ">");
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_heredoc_or_input(t_token **head, const char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		create_and_add_token(head, T_HEREDOC, "<<");
		*i += 2;
		return (1);
	}
	else if (input[*i] == '<')
	{
		create_and_add_token(head, T_REDIRECT_IN, "<");
		(*i)++;
		return (1);
	}
	return (0);
}

int	is_pipe_token(t_token **head, const char *input, int *i)
{
	if (input[*i] == '|')
	{
		create_and_add_token(head, T_PIPE, "|");
		(*i)++;
		return (1);
	}
	return (0);
}

void	process_token(t_token **head, const char *input, int *i)
{
	if (is_pipe_token(head, input, i))
		return ;
	else if (is_heredoc_or_input(head, input, i))
		return ;
	else if (is_append_or_output(head, input, i))
		return ;
	else
		get_word(head, input, i);
}

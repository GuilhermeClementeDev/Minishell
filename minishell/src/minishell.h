/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/04 19:38:08 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0

# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT_IN 3
# define T_REDIRECT_OUT 4
# define T_APPEND 5
# define T_HEREDOC 6

typedef struct s_token
{
	int		type;
	char	*value;
	struct s_token	*next;
}	t_token;

int	ft_not_only_spaces(char *str);

//verify_input.c
int	verify_quotes(const char *str);
int	verify_redirects(const char *str);
int check_syntax_error(const char *str);

//verify_input_utils.c
int	inside_quotes(const char *str, int i);
int	is_delimiter(char c);

int	is_double_operator(const char *str, int i);
int	is_pipe_space_pipe(const char *str, int *i);

//lexer.c
t_token	*lexer(const char *input);
t_token	*create_token(int type, char *value);
void	create_and_add_token(t_token **head, int type, char *value);

//lexer_utils.c
void get_word(t_token **head ,const char *input, int *i);
void	clean_tokens(t_token *head);

//lexer_tokens.c
int	is_append_or_output(t_token **head, const char *input, int *i);
int	is_heredoc_or_input(t_token **head, const char *input, int *i);
int	is_pipe_token(t_token **head, const char *input, int *i);
void	process_token(t_token **head, const char *input, int *i);

#endif

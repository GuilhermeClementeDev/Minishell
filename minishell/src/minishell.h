/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/14 14:58:58 by gda-conc         ###   ########.fr       */
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
# define T_RED_IN 3
# define T_RED_OUT 4
# define T_APPEND 5
# define T_HEREDOC 6

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	int					type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char			**args;
	t_redirect		*redirects;
	struct s_cmd	*next;
}	t_cmd;

int			ft_not_only_spaces(char *str);

//verify_input.c
int			verify_quotes(const char *str);
int			verify_redirects(const char *str);
int			check_syntax_error(const char *str);

//verify_input_utils.c
int			inside_quotes(const char *str, int i);
int			is_delimiter(char c);

int			is_double_operator(const char *str, int i);
int			is_pipe_space_pipe(const char *str, int *i);

//lexer.c
t_token		*lexer(const char *input);
t_token		*create_token(int type, char *value);
void		create_and_add_token(t_token **head, int type, char *value);

//lexer_utils.c
void		get_word(t_token **head, const char *input, int *i);
void		clean_tokens(t_token *head);

//lexer_tokens.c
int			is_append_or_output(t_token **head, const char *input, int *i);
int			is_heredoc_or_input(t_token **head, const char *input, int *i);
int			is_pipe_token(t_token **head, const char *input, int *i);
void		process_token(t_token **head, const char *input, int *i);

//parser.c
t_cmd		*parse_tokens(t_token *token);

//parser_utils.c
int			handle_redirect(t_token **token, t_redirect **redirects);
int			is_redirect_type(int type);

//free_elements.c
void		free_token_list(t_token *head);
void		free_redirects(t_redirect *redirects);
void		free_commands(t_cmd *cmds);

//var_expansion.c
void		expand_variables_in_token(t_token *token);
char		*expand_variable(const char *input, int *index);

//var_expansion_utils.c
int			quoted_part(const char *input, int *i, char **expanded_str);
int			var_expansion(const char *input, int *i, char **expanded_str);
int			handle_normal_char(const char *input, int *i, char **expand_str);
char		*initialize_expanded_str(void);
int			quotes_or_expansion(char **exp_str, const char *input, int *i);

//prints.c
void		print_tokens(t_token **head);
void		print_cmds(t_cmd **cmd);

//prints_utils.c
const char	*token_type_to_str(int type);
const char	*redir_type_to_str(int type);

#endif

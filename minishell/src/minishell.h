/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/04/27 11:47:24 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0

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

#endif

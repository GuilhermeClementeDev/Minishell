/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/04/19 15:47:11 by gda-conc         ###   ########.fr       */
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
int check_syntax_error(const char *str);

//verify_input_utils.c
int	inside_quotes(const char *str, int i);
int	is_delimiter(char c);
int next_is_valid(const char *str, int start);

#endif

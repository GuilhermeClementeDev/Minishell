/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/08 18:53:52 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <linux/limits.h>

# define TRUE 1
# define FALSE 0

int		ft_not_only_spaces(char *str);
char	*get_env_value(char **envp, const char *key);
int		count_env(char **env);


void	ft_error(char *str, int n);

void	ft_echo(char **str);
void	ft_pwd(void);
void	ft_env(char **envp);
void	ft_cd(char **str, char **envp);
void	ft_exit(char **args);


#endif

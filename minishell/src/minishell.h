/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:02:48 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/14 14:30:52 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>

# define TRUE 1
# define FALSE 0

//utilits
int		ft_not_only_spaces(char *str);

//utilits_env
char	*get_env_value(char **envp, char *key);
int		count_env(char **env);
char	**alloc_env(int entry_count);
void	copy_env_skip(char **old_env, char **new_env, \
							char *skip, char *new_var);

//utilits_export
int		is_valid_export(char *str);
char	*ft_no_spaces(char *str);
int		ft_change_value(char **env, char *new_var);

//error
void	ft_error(char *str, int n);
void	free_env(char **env);

//builtins1
void	ft_echo(char **str);
void	ft_pwd(void);
void	ft_env(char **envp);
void	ft_cd(char **str, char **envp);
void	ft_exit(char **args);

//builtins2
char	**ft_export(char **env, char *new_var);
char	**ft_unset(char **env, char *to_remove);

#endif

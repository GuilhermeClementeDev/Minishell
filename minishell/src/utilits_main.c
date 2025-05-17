/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:46:09 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/16 22:53:50 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_shlvl(char **env)
{
	char	*shlvl;
	int		i;

	i = 0;
	shlvl = get_env_value(env, "SHLVL");
	if (!shlvl)
		return (0);
	while (shlvl[i] && ft_isdigit(shlvl[i]))
		i++;
	if (shlvl[i] == '\0')
		return (ft_atoi(shlvl));
	return (0);
}

static void	ft_shlvl(t_shell *shell)
{
	int		shlvl_int;
	char	*shlvl_str;
	char	*tmp;

	shlvl_int = ft_check_shlvl(shell->env);
	if (shlvl_int)
	{
		shlvl_int++;
		tmp = ft_itoa(shlvl_int);
		shlvl_str = ft_strjoin("SHLVL=", tmp);
		ft_change_value(shell->env, shlvl_str);
		free(shlvl_str);
		free(tmp);
	}
	else
		shell->env = ft_export(shell->env, "SHLVL=1");
}

void	ft_build_shell(t_shell *shell, char **envp)
{
	shell->env = alloc_env(count_env(envp));
	copy_env_skip(envp, shell->env, NULL, NULL);
	ft_shlvl(shell);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
}

void	ft_clean_shell(t_shell *shell)
{
	free_input_token_cmd(shell->input, shell->tokens, shell->cmds);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
}

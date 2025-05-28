/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:46:09 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/28 14:13:28 by guclemen         ###   ########.fr       */
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
	char	**vars;

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
	{
		vars = single_var("SHLVL=1");
		if (vars)
		{
			ft_export(shell->env, vars, shell);
			free(vars);
		}
	}
}

static void	ft_env_pwd(t_shell	*shell)
{
	char	**new_env;
	char	cwd[PATH_MAX];
	char	*pwd;

	getcwd(cwd, sizeof(cwd));
	pwd = ft_strjoin("PWD=", cwd);
	if (!get_env_variable(shell->env, "PWD"))
	{
		new_env = single_var(pwd);
		ft_export(shell->env, new_env, shell);
		free(new_env);
	}
	else
		ft_change_value(shell->env, pwd);
	free(pwd);
	if (!get_env_variable(shell->env, "OLDPWD"))
	{
		new_env = single_var("OLDPWD");
		ft_export(shell->env, new_env, shell);
		free(new_env);
	}
}

void	ft_build_shell(t_shell *shell, char **envp)
{
	shell->env = alloc_env(count_env(envp));
	copy_env_skip(envp, shell->env, NULL, NULL);
	ft_shlvl(shell);
	ft_env_pwd(shell);
	shell->status = 0;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
}

void	ft_clean_shell(t_shell *shell)
{
	free_input_token_cmd(shell->input, shell->cmds);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
}

int	is_space_or_invalid(char *input)
{
	if (!ft_not_only_spaces(input))
	{
		free(input);
		input = NULL;
		return (1);
	}
	if (check_syntax_error(input))
	{
		free(input);
		input = NULL;
		return (1);
	}
	return (0);
}

t_token	*list_token(char *input, t_shell *shell)
{
	t_token	*token_list;

	token_list = lexer(input);
	expand_variables_in_token(token_list, shell);
	clean_tokens(token_list);
	return (token_list);
}

void	free_input_token_cmd(char *input, t_cmd *cmd_list)
{
	if (input)
		free(input);
	if (cmd_list)
		free_commands(cmd_list);
}

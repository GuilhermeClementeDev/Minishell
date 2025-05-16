/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:19:25 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/15 23:03:24 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	int		size;

	size = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", size) || !ft_strncmp(cmd, "pwd", size) || !ft_strncmp(cmd, "exit", size) || !ft_strncmp(cmd, "export", size) || !ft_strncmp(cmd, "unset", size) || !ft_strncmp(cmd, "env", size) || !ft_strncmp(cmd, "echo", size))
		return (1);
	return (0);
}

void	execute_builtin(t_cmd *cmd, char **env)
{
	char	*comand;
	int		size;
	pid_t	pid;

	comand = cmd->args[0];
	size = ft_strlen(comand);
	if (!ft_strncmp(comand, "cd", size))
		ft_cd(cmd->args, env);
	else if (!ft_strncmp(comand, "exit", size))
		ft_exit(cmd->args);
	else if (!ft_strncmp(comand, "export", size))
		ft_export(env, cmd->args[1]);
	else if (!ft_strncmp(comand, "unset", size))
		ft_unset(env, cmd->args[1]);

	pid = fork();
	if (pid == 0)
	{
		/*
		if (cmd->fd_out != 1)
		{
			dup2(cmd->fd_out, 1);
			close(cmd->fd_out);
		}
		if (cmd->fd_in != 0)
		{
			dup2(cmd->fd_in, 0);
			close(cmd->fd_in);
		}*/
		if (!ft_strncmp(comand, "echo", size))
			ft_echo(cmd->args);
		else if (!ft_strncmp(comand, "pwd", size))
			ft_pwd();
		else if (!ft_strncmp(comand, "env", size))
			ft_env(env);
		exit(0);
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
	}
	else
		perror("fork");
}

void ft_executer(t_cmd *cmd, char **env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
		execute_builtin(cmd, env);
	else
		printf("Executável externo ainda não implementado: %s\n", cmd->args[0]);
}

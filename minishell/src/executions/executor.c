/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:19:25 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/04 01:08:10 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*command;
	int		status;

	status = 1;
	command = cmd->args[0];
	check_error_and_dup(shell, cmd);
	if (!ft_strncmp(command, "echo", 5))
		status = ft_echo(cmd->args);
	else if (!ft_strncmp(command, "pwd", 4))
		status = ft_pwd();
	else if (!ft_strncmp(command, "env", 4))
		status = ft_env(shell->env);
	else if (!ft_strncmp(command, "cd", 3))
		status = ft_cd(shell, cmd->args, shell->env);
	else if (!ft_strncmp(command, "exit", 5))
		ft_exit(shell, cmd);
	else if (!ft_strncmp(command, "export", 7))
		status = ft_export(shell->env, cmd->args, shell);
	else if (!ft_strncmp(command, "unset", 6))
		status = ft_unset(shell->env, cmd->args, shell);
	free_and_exit(shell, status);
}

static int	execute_builtin_parent(t_shell *shell, t_cmd *cmd)
{
	char	*command;
	int		status;

	status = 1;
	command = cmd->args[0];
	if (!ft_strncmp(command, "cd", 3))
		status = ft_cd(shell, cmd->args, shell->env);
	else if (!ft_strncmp(command, "exit", 5))
		ft_exit(shell, cmd);
	else if (!ft_strncmp(command, "export", 7))
		status = ft_export(shell->env, cmd->args, shell);
	else if (!ft_strncmp(command, "unset", 6))
		status = ft_unset(shell->env, cmd->args, shell);
	return (status);
}

void	execute_external_func(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	check_error_and_dup(shell, cmd);
	if (cmd->args[0] == NULL && cmd->redirects)
		free_and_exit(shell, 0);
	path = find_cmd_path(shell, cmd);
	if (!path)
	{
		print_error(cmd->args[0], NULL, "command not found");
		free_and_exit(shell, 127);
	}
	if (check_exec_path(path))
	{
		free(path);
		free_and_exit(shell, EXIT_FAILURE);
	}
	execve(path, cmd->args, shell->env);
	free(path);
	free_and_exit(shell, EXIT_FAILURE);
}

void	execute_in_fork(pid_t pid, t_shell *shell, t_cmd *cmd)
{
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (is_builtin(cmd->args[0]))
			execute_builtin(shell, cmd);
		else
			execute_external_func(shell, cmd);
	}
}

void	ft_executer(t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		status;

	cmd = shell->cmds;
	while (cmd)
	{
		if (!shell->cmds->next && is_builtin(cmd->args[0]) == 1)
		{
			g_status = execute_builtin_parent(shell, cmd);
			cmd = cmd->next;
			continue ;
		}
		pid = fork();
		execute_in_fork(pid, shell, cmd);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
	signal(SIGINT, sigint_exec_handler);
	while (wait(&status) > 0)
		ft_signals_child(status);
}

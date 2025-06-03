/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:19:25 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/02 22:01:01 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exec_path(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
	{
		if (errno == ENOENT)
			print_error((char *)path, NULL, "No such file or directory");
		else
			perror(path);
		return (-1);
	}
	if (S_ISDIR(sb.st_mode))
	{
		print_error((char *)path, NULL, "Is a directory");
		return (-1);
	}
	if (access(path, X_OK) == -1)
	{
		if (errno == EACCES)
			print_error((char *)path, NULL, "Permission denied");
		else
			perror(path);
		return (-1);
	}
	return (0);
}

void	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*command;
	int		status;

	status = 1;
	command = cmd->args[0];
	if (cmd->redirect_error)
	{
		check_exec_path(cmd->filename_error);
		close_cmd_fds(shell->cmds); //liberar tudo
		ft_clean_shell(shell);
		free_env(shell->env);
		free(shell);
		exit(1);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
//Fecha todos os FDs abertos dos comandos, exceto os padrões
	close_cmd_fds(shell->cmds);
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
	ft_clean_shell(shell);
	free_env(shell->env);
	free(shell);
	exit(status);
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

	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->redirect_error)
	{
		check_exec_path(cmd->filename_error);
		close_cmd_fds(shell->cmds); //liberar tudo
		ft_clean_shell(shell);
		free_env(shell->env);
		free(shell);
		exit(1);
	}
	if (cmd->args[0] == NULL && cmd->redirects)
	{
		close_cmd_fds(shell->cmds); //liberar tudo
		ft_clean_shell(shell);
		free_env(shell->env);
		free(shell);
		exit(0);
	}
 //liberar tudo // Fecha todos os FDs abertos dos comandos, exceto os padrões
	close_cmd_fds(shell->cmds);
	path = find_cmd_path(shell, cmd);
	if (!path)
	{
		print_error(cmd->args[0], NULL, "command not found");
		close_cmd_fds(shell->cmds); //liberar tudo
		ft_clean_shell(shell);
		free_env(shell->env);
		free(shell);
		exit(127);
	}
	if (check_exec_path(path))
	{
		free(path);
		close_cmd_fds(shell->cmds); //liberar tudo
		ft_clean_shell(shell);
		free_env(shell->env);
		free(shell);
		exit(EXIT_FAILURE);
	}
	execve(path, cmd->args, shell->env);
	free(path);
	close_cmd_fds(shell->cmds); //liberar tudo
	ft_clean_shell(shell);
	free_env(shell->env);
	free(shell);
	exit(EXIT_FAILURE);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:19:25 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/25 13:49:26 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	int		size;

	size = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", size) || !ft_strncmp(cmd, "pwd", size) || \
	!ft_strncmp(cmd, "exit", size) || !ft_strncmp(cmd, "export", size) || \
	!ft_strncmp(cmd, "unset", size) || !ft_strncmp(cmd, "env", size) || \
	!ft_strncmp(cmd, "echo", size))
		return (1);
	return (0);
}

void	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*command;
	pid_t	pid;

	command = cmd->args[0];
	if (!ft_strncmp(command, "cd", 3))
		ft_cd(shell ,cmd->args, shell->env);
	else if (!ft_strncmp(command, "exit", 5))
		ft_exit(shell);
	else if (!ft_strncmp(command, "export", 7))
		shell->env = ft_export(shell->env, cmd->args);
	else if (!ft_strncmp(command, "unset", 6))
		shell->env = ft_unset(shell->env, cmd->args);

	//fazer verificação se há outro comando (pipe), executar built ins no
	//filho e não no pai se tiver
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if(cmd->redirect_error)
			{
				perror("Redirection error");
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

			if (!ft_strncmp(command, "echo", 5))
				ft_echo(cmd->args);
			else if (!ft_strncmp(command, "pwd", 4))
				ft_pwd();
			else if (!ft_strncmp(command, "env", 4))
				ft_env(shell->env);

			exit(0);
		}
		else if (pid > 0)
			waitpid(pid, NULL, 0);
		else
			perror("fork");
	}
}
char	*find_cmd_path(t_shell *shell, t_cmd *cmd)
{
	char	**paths;
	char	*path_env;
	int		i;

	i = 0;
	path_env = get_env_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	while (paths[i])
	{
		path_env = ft_strjoin(paths[i], "/");
		path_env = ft_join_gnl(path_env, cmd->args[0]);
		if (access(path_env, X_OK) == 0)
		{
			free_env(paths);
			return (path_env);
		}
		free(path_env);
		i++;
	}
	free_env(paths);
	return (NULL);
}
void	execute_external_func(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	pid_t	pid;

	path = find_cmd_path(shell, cmd);
	if (!path)
	{
		ft_putstr_fd("-bash: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		//possivelmente librerar aqui
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if(cmd->redirect_error)
		{
			perror("Redirection error");
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
		execve(path, cmd->args, shell->env);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
	free(path);
}

void	ft_executer(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	while(cmd)
	{
		if (is_builtin(cmd->args[0]))
			execute_builtin(shell, cmd);
		else
			execute_external_func(shell, cmd);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
}

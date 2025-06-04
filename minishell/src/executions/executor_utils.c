/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:54:17 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/04 01:08:58 by bieldojt         ###   ########.fr       */
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

int	is_builtin(char *cmd)
{
	int		size;

	if (!cmd)
		return (0);
	size = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", size) || !ft_strncmp(cmd, "exit", size) \
	|| !ft_strncmp(cmd, "export", size) || !ft_strncmp(cmd, "unset", size))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", size) || !ft_strncmp(cmd, "env", size) \
	|| !ft_strncmp(cmd, "echo", size))
		return (2);
	return (0);
}

char	*find_cmd_path(t_shell *shell, t_cmd *cmd)
{
	char	**paths;
	char	*path_env;
	int		i;

	if (ft_strchr(cmd->args[0], '/'))
		return (ft_strdup(cmd->args[0]));
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

void	free_and_exit(t_shell *shell, int exit_code)
{
	close_cmd_fds(shell->cmds);
	ft_clean_shell(shell);
	free_env(shell->env);
	free(shell);
	exit(exit_code);
}

void	check_error_and_dup(t_shell *shell, t_cmd *cmd)
{
	if (cmd->redirect_error)
	{
		check_exec_path(cmd->filename_error);
		free_and_exit(shell, 1);
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
	close_cmd_fds(shell->cmds);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:19:25 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/28 15:35:02 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	int		size;
	if (!cmd)
		return (0);
	size = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", size) || !ft_strncmp(cmd, "exit", size) \
	|| !ft_strncmp(cmd, "export", size) || !ft_strncmp(cmd, "unset", size))
		return (1);
	else if( !ft_strncmp(cmd, "pwd", size) || !ft_strncmp(cmd, "env", size) \
	|| !ft_strncmp(cmd, "echo", size))
		return (2);
	return (0);
}

void	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*command;
	int		status;

	status = 1;
	command = cmd->args[0];

	if(cmd->redirect_error)
	{
		perror("Redirection error");
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
	close_cmd_fds(shell->cmds); // Fecha todos os FDs abertos dos comandos, exceto os padrões
	if (!ft_strncmp(command, "echo", 5))
		status = ft_echo(cmd->args);
	else if (!ft_strncmp(command, "pwd", 4))
		status = ft_pwd();
	else if (!ft_strncmp(command, "env", 4))
		status = ft_env(shell->env);
	else if (!ft_strncmp(command, "cd", 3))
		status = ft_cd(shell ,cmd->args, shell->env);
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
		status = ft_cd(shell ,cmd->args, shell->env);
	else if (!ft_strncmp(command, "exit", 5))
		ft_exit(shell, cmd);
	else if (!ft_strncmp(command, "export", 7))
		status = ft_export(shell->env, cmd->args, shell);
	else if (!ft_strncmp(command, "unset", 6))
		status = ft_unset(shell->env, cmd->args, shell);
	return (status);
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
	if(cmd->redirect_error)
	{
		perror("Redirection error");
		close_cmd_fds(shell->cmds); //liberar tudo
		ft_clean_shell(shell);
		free_env(shell->env);
		free(shell);
		exit(1);
	}
	if(cmd->args[0] == NULL && cmd->redirects)
	{
		close_cmd_fds(shell->cmds); //liberar tudo
		ft_clean_shell(shell);
		free_env(shell->env);
		free(shell);
		exit(0);
	}

	close_cmd_fds(shell->cmds); //liberar tudo // Fecha todos os FDs abertos dos comandos, exceto os padrões
	path = find_cmd_path(shell, cmd);
	if (!path)
	{
		ft_putstr_fd("-bash: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		close_cmd_fds(shell->cmds); //liberar tudo
		ft_clean_shell(shell);
		free_env(shell->env);
		free(shell);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror("execve");
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
	while(cmd)
	{
		if(!shell->cmds->next && is_builtin(cmd->args[0]) == 1)
		{
			shell->status = execute_builtin_parent(shell, cmd);
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
		ft_signals_child(status, shell);
	// Espera todos os processos filhos terminarem
}

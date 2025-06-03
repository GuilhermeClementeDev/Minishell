/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:54:17 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/02 21:56:12 by guclemen         ###   ########.fr       */
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

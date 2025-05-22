/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:15:18 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/22 19:14:53 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_not_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || !(str[i] >= '\t' && str[i] <= '\r'))
			break ;
		i++;
	}
	if (str[i])
		return (1);
	return (0);
}
int	get_env_variable(char **env, char *key)
{
	int	i;
	int	j;

	if (!env || !key)
		return (0);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (key[j] && env[i][j] == key[j])
			j++;
		if (key[j] == '\0' && (env[i][j] == '=' || env[i][j] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

int	is_env_skip_match(char *env_var, char *skip)
{
	int	len;

	if (!env_var || !skip)
		return (0);
	len = ft_strlen(skip);
	if (ft_strncmp(env_var, skip, len) != 0)
		return (0);
	if (env_var[len] != '=' && env_var[len] != '\0')
		return (0);
	return (1);
}
static char	*ft_build_path(char **separated)
{
	char	*absolute_path;
	int		i;

	i = 0;
	absolute_path = ft_strdup("/");
	while(separated[i])
	{
		absolute_path = ft_join_gnl(absolute_path, separated[i]);
		if (separated[i + 1])
			absolute_path = ft_join_gnl(absolute_path, "/");
		i++;
	}
	free_env(separated);
	return (absolute_path);
}

char	*ft_full_path(char *current_pwd, char *goal)
{
	char	*path;
	char	**separated;
	char	**path_helper;
	int		i;
	int		last;

	i = 0;
	last = 0;
	path = ft_strjoin(current_pwd, "/");
	path = ft_join_gnl(path, goal);
	separated = ft_split(path, '/');
	free(goal);
	free(path);
	path_helper = malloc(sizeof(char *) * (count_env((separated)) + 1));
	while (separated[i])
	{
		if (ft_strncmp(separated[i], "..", ft_strlen(separated[i])) == 0 && last > 0)
			free(path_helper[--last]);
		else if (ft_strncmp(separated[i], ".", ft_strlen(separated[i])) != 0 && ft_strncmp(separated[i], "", ft_strlen(separated[i])) != 0)
			path_helper[last++] = ft_strdup(separated[i]);
		i++;
	}
	path_helper[last] = NULL;
	free_env(separated);
	return (ft_build_path(path_helper));
}

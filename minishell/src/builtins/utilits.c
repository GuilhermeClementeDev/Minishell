/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:15:18 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/22 16:20:54 by guclemen         ###   ########.fr       */
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
/*
char	*ft_absolute_path(char *current_pwd, char *target)
{
	char	*joined;
	char	**parts;
	char	**resolved;
	int		i, j;

	if (target[0] == '/')
		return (ft_strdup(target));

	joined = ft_strjoin(current_pwd, "/");
	joined = strjoin_free(joined, target);
	parts = ft_split(joined, '/');
	resolved = malloc(sizeof(char *) * (count_strings(parts) + 1));
	i = 0;
	j = 0;
	while (parts[i])
	{
		if (ft_strcmp(parts[i], "..") == 0 && j > 0)
			j--; // sobe um diretório
		else if (ft_strcmp(parts[i], ".") != 0 && ft_strlen(parts[i]) > 0)
			resolved[j++] = ft_strdup(parts[i]);
		i++;
	}
	resolved[j] = NULL;
	free(joined);
	free_split(parts);
	return (join_path(resolved));
}
*/

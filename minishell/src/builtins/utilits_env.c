/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:09:42 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/14 14:38:32 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char **envp, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (key[j] && envp[i][j] == key[j])
			j++;
		if (key[j] == '\0' && envp[i][j] == '=')
			return (&envp[i][j + 1]);
		i++;
	}
	return (NULL);
}

int	count_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

char	**alloc_env(int entry_count)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (entry_count + 1));
	if (!new_env)
		return (NULL);
	new_env[entry_count] = NULL;
	return (new_env);
}

void	copy_env_skip(char **old_env, char **new_env, char *skip, char *new_var)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (old_env[i])
	{
		if (skip)
		{
			if (ft_strnstr(old_env[i], skip, ft_strlen(skip)))
			{
				if (new_var)
					new_env[k++] = ft_strdup(new_var);
				i++;
				continue ;
			}
		}
		new_env[k] = ft_strdup(old_env[i]);
		i++;
		k++;
	}
	if (new_var && !skip)
		new_env[k] = ft_strdup(new_var);
}

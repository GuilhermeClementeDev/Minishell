/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:17:20 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/08 18:57:49 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_export(char **str, char **envp)
{
	int	env_count;
	char	**new_env;
	int	i;

	i = 0;
	if (!str[1])
		return (envp);
	env_count = count_env(envp);
	new_env = malloc(sizeof(char *) * (env_count + 2));
	if (!new_env)
		return (NULL);
	while (i < env_count)
	{
		new_env[i] = ft_strdup((*cp_env)[i]);
		i++;
	}

	new_env[i] = strdup(argv[1]);
	if (!new_env[i])
	{
		free_env(new_env);
		return;
	}
	i++;
	new_env[i] = NULL;

	free_env(*cp_env);
	*cp_env = new_env;
}


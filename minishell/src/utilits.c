/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:15:18 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/01 14:59:48 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_env_value(char **envp, const char *key)
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

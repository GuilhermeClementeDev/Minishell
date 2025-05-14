/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:28:11 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/14 14:38:27 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_msg(char *str, int n)
{
	int	std;

	if (n == 0)
	{
		std = 1;
		ft_putstr_fd(str, std);
	}
	else
	{
		std = 2;
		ft_putstr_fd("Error :(\n", std);
		ft_putstr_fd(str, std);
	}
}

void	ft_error(char *str, int n)
{
	ft_msg(str, n);
	exit(n);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

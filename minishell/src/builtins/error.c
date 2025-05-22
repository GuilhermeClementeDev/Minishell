/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:28:11 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/22 11:37:28 by guclemen         ###   ########.fr       */
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

void	print_error(char *cmd, char *str, char *msg)
{
	ft_putstr_fd("bash: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
	{
		if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
			ft_putchar_fd('\'', 2);
		ft_putstr_fd(str, 2);
		if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
			ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

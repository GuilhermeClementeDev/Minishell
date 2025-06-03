/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_builtins2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:28:31 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/02 21:44:18 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_only_chr(char *str, char a)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != a)
			return (1);
		i++;
	}
	return (0);
}

void	validate_path_helper(char **separated, char **path_helper)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (separated[i])
	{
		if (ft_strncmp(separated[i], "..", \
ft_strlen(separated[i])) == 0 && last > 0)
			free(path_helper[--last]);
		else if (ft_strncmp(separated[i], ".", ft_strlen(separated[i])) != 0 \
&& ft_strncmp(separated[i], "", ft_strlen(separated[i])) != 0)
			path_helper[last++] = ft_strdup(separated[i]);
		i++;
	}
	path_helper[last] = NULL;
}

int	exit_status(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return ((unsigned char)ft_atoi(str));
	print_error("exit", str, "numeric argument required");
	return (2);
}

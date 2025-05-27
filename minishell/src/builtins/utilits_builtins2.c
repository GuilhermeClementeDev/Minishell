/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_builtins2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:28:31 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/27 16:33:14 by guclemen         ###   ########.fr       */
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

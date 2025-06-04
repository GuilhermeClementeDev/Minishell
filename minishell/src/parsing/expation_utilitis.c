/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expation_utilitis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:57:21 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/02 20:57:55 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	handle_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
	{
		*in_single = !(*in_single);
		return (1);
	}
	else if (c == '\"' && !(*in_single))
	{
		*in_double = !(*in_double);
		return (1);
	}
	return (0);
}

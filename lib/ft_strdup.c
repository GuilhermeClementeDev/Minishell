/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:46:35 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/22 18:34:03 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*ptr;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	ptr = (char *)malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, size + 1);
	return (ptr);
}

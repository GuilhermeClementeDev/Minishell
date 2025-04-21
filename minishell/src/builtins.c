/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:56:02 by guclemen          #+#    #+#             */
/*   Updated: 2025/04/21 17:41:09 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **str)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (str[i] && ft_strncmp(str[i], "-n", ft_strlen(str[i])) == 0)
	{
		flag = 1;
		i++;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}
/* //testes das funções na mão
int main(void)
{
	// Testes ft_echo
	printf("Teste 1: echo hello world\n");
	ft_echo((char *[]){"echo", "hello", "world", NULL});

	printf("Teste 2: echo -n sem quebra de linha\n");
	ft_echo((char *[]){"echo", "-n", "sem", "quebra", "de", "linha", NULL});

	printf("Teste 3: echo sem argumentos\n");
	ft_echo((char *[]){"echo", NULL});

	printf("Teste 4: echo -n sozinho\n");
	ft_echo((char *[]){"echo", "-n", NULL});

	return 0;
}
*/

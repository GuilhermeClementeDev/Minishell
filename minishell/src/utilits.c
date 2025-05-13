/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:15:18 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/13 16:08:25 by guclemen         ###   ########.fr       */
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
char **alloc_env(int entry_count)
{
	char **new_env;

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
				{
					new_env[k] = ft_strdup(new_var);
					k++;
				}
				i++;
			}
		}
		if(!old_env[i])
			break;
		new_env[k] = ft_strdup(old_env[i]);
		i++;
		k++;
	}
	if (new_var && !skip)
		new_env[k] = ft_strdup(new_var);
}
/*
int main(void) {
    // O ambiente simulado já termina com NULL
    char *test_env[] = {
        "USER=guest",
        "PATH=/usr/bin:/bin",
        "HOME=/home/guest",
        NULL
    };

    // Imprime tamanho do env original
    int orig_count = count_env(test_env);
    printf("Original environment (%d entries):\n", orig_count +1);
    for (int i = 0; i < orig_count; i++)
        printf("  %s\n", test_env[i]);
    printf("\n");

    // Exemplo 1: cópia normal sem adicionar nem remover
    char *skip = NULL;
    char *add = NULL;
    int target0 = orig_count;
    printf("[1] Alocando %d pointers para cópia normal\n", target0 + 1);
    char **env0 = alloc_env(target0);
    if (!env0) return 1;
    copy_env_skip(test_env, env0, skip, add);
    printf("Copy without skip or add (%d entries):\n", count_env(env0));
    for (int i = 0; env0[i]; i++) {
        printf("  %s\n", env0[i]);
        free(env0[i]);
    }
    free(env0);
    printf("\n");

    // Exemplo 2: apenas pular a variável PATH
    skip = "PATH=";
    add = NULL;
    int target1 = orig_count - 1;
    printf("[2] Alocando %d pointers para skip PATH\n", target1 +1);
    char **env1 = alloc_env(target1);
    if (!env1) return 1;
    copy_env_skip(test_env, env1, skip, add);
    printf("After skip PATH= (%d entries):\n", count_env(env1));
    for (int i = 0; env1[i]; i++) {
        printf("  %s\n", env1[i]);
        free(env1[i]);
    }
    free(env1);
    printf("\n");

    // Exemplo 3: adicionar MYVAR=hello
    skip = NULL;
    add = "MYVAR=hello";
    int target2 = orig_count + 1;
    printf("[3] Alocando %d pointers para adicionar MYVAR=hello\n", target2 +1);
    char **env2 = alloc_env(target2);
    if (!env2) return 1;
    copy_env_skip(test_env, env2, skip, add);
    printf("After add MYVAR=hello (%d entries):\n", count_env(env2));
    for (int i = 0; env2[i]; i++) {
        printf("  %s\n", env2[i]);
        free(env2[i]);
    }
    free(env2);
    printf("\n");

    // Exemplo 4: pular HOME e adicionar NEW=1
    skip = "HOME=";
    add = "NEW=1";
    int target3 = orig_count - 1 + 1;
    printf("[4] Alocando %d pointers para skip HOME e add NEW=1\n", target3 +1);
    char **env3 = alloc_env(target3);
    if (!env3) return 1;
    copy_env_skip(test_env, env3, skip, add);
    printf("After skip HOME= and add NEW=1 (%d entries):\n", count_env(env3));
    for (int i = 0; env3[i]; i++) {
        printf("  %s\n", env3[i]);
        free(env3[i]);
    }
    free(env3);

    return 0;
}
*/

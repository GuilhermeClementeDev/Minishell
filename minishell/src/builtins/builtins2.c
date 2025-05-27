/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:17:20 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/27 15:34:42 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_export(char **env, char **new_var)
{
	char	**new_env;
	char	**tmp;
	int		i;

	i = 1;
	new_env = env;
	if (!new_var[i])
		ft_print_export(env);
	while (new_var[i])
	{
		if (is_valid_export(new_var[i]))
		{
			if (!ft_change_value(new_env, new_var[i]))
			{
				tmp = alloc_env(count_env(new_env) + 1);
				copy_env_skip(new_env, tmp, NULL, new_var[i]);
				free_env(new_env);
				new_env = tmp;
			}
		}
		i++;
	}
	return (new_env);
}

char	**ft_unset(char **env, char **to_remove)
{
	char	**new_env;
	char	**tmp;
	int		i;

	i = 1;
	new_env = env;
	while (to_remove[i])
	{
		if (get_env_variable(new_env, to_remove[i]))
		{
			tmp = alloc_env(count_env(new_env) - 1);
			copy_env_skip(new_env, tmp, to_remove[i], NULL);
			free_env(new_env);
			new_env = tmp;
		}
		i++;
	}
	return (new_env);
}
/*
int main(void) {
    char *test_env[] = {
        "USER=guest",
        "PATH=/usr/bin:/bin",
        "HOME=/home/guest",
        NULL
    };

    char **env = alloc_env(count_env(test_env));
    for (int i = 0; test_env[i]; i++)
        env[i] = strdup(test_env[i]);

    printf("Original environment (%d entries):\n", count_env(env));
    for (int i = 0; env[i]; i++)
        printf("  [%d] %s\n", i, env[i]);
    printf("\n");

    env = ft_export(env, "   TEST1=hello");
    env = ft_export(env, "TEST2=world");
    env = ft_export(env, "INVALID");
    env = ft_export(env, "=oops");
    env = ft_export(env, "    \tMYVAR=withtabs");
    env = ft_export(env, "SINGLECHAR=A");
    env = ft_export(env, "    KEY=   spacedvalue");
    env = ft_export(env, "MIXED=   content with spaces   ");
    env = ft_export(env, "TEST2=vasco");

    printf("After export tests (%d entries):\n", count_env(env));
    for (int i = 0; env[i]; i++)
        printf("  [%d] %s\n", i, env[i]);
    printf("\n");

    env = ft_unset(env, "PATH");
    env = ft_unset(env, "NONEXISTENT");

    printf("After unset tests (%d entries):\n", count_env(env));
    for (int i = 0; env[i]; i++)
        printf("  [%d] %s\n", i, env[i]);
    printf("\n");

    free_env(env);
    return 0;
}*/

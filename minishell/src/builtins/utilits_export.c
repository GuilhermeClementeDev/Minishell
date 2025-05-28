/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:06:49 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/28 14:58:28 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_export(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
	{
		print_error("export", str, "not a valid identifier");
		return (0);
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			print_error("export", str, "not a valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_change_value(char **env, char *new_var)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	i = 0;
	while (new_var[len] && new_var[len] != '=')
		len++;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (len == j && ft_strncmp(env[i], new_var, len) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(new_var);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**single_var(char *var)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	arr[0] = "export";
	arr[1] = var;
	arr[2] = NULL;
	return (arr);
}

static char	**ft_sort_env(char **env)
{
	int		i;
	int		k;
	char	*tmp;
	char	**sorted_env;

	i = 0;
	sorted_env = alloc_env(count_env(env));
	copy_env_skip(env, sorted_env, NULL, NULL);
	while (sorted_env[i])
	{
		k = i + 1;
		while (sorted_env[k])
		{
			if (ft_strncmp(sorted_env[i], sorted_env[k], \
				ft_strlen(sorted_env[i])) > 0)
			{
				tmp = sorted_env[i];
				sorted_env[i] = sorted_env[k];
				sorted_env[k] = tmp;
			}
			k++;
		}
		i++;
	}
	return (sorted_env);
}

void	ft_print_export(char **env)
{
	int		i;
	int		k;
	char	**sorted_env;

	i = 0;
	sorted_env = ft_sort_env(env);
	while (sorted_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(sorted_env[i], '='))
		{
			k = 0;
			while (sorted_env[i][k] != '=')
				ft_putchar_fd(sorted_env[i][k++], 1);
			write(1, "=\"", 2);
			while (sorted_env[i][++k])
				ft_putchar_fd(sorted_env[i][k], 1);
			write(1, "\"", 1);
		}
		else
			write(1, sorted_env[i], ft_strlen(sorted_env[i]));
		write(1, "\n", 1);
		i++;
	}
	free_env(sorted_env);
}

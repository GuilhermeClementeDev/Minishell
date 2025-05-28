/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:56:02 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/28 15:15:29 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **str)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (str[i] && ft_strncmp(str[i], "-n", 2) == 0 \
	&& ft_only_chr(&str[i][1], 'n') == 0)
	{
		flag = 1;
		i++;
	}
	while (str[i])
	{
		if (str[i][0] != '\0')
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
		}
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	return (1);
}

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	ft_cd(t_shell *shell, char **str, char **envp)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (str[1])
		path = ft_strdup(str[1]);
	else
		path = ft_strdup(get_env_value(envp, "HOME"));
	if (!path)
	{
		print_error("cd", NULL, "HOME not set");
		return (1);
	}
	if (path[0] != '/')
		path = ft_full_path(getcwd(cwd, sizeof(cwd)), path);
	if (chdir(path) != 0)
	{
		print_error("cd", (char *)path, "No such file or directory");
		free(path);
		return (1);
	}
	ft_new_env_pwds(shell);
	free(path);
	return (0);
}

void	ft_exit(t_shell *shell , t_cmd *cmd)
{
	int		status;
	char	*str;
	int		i;

	status = 0;
	i = 0;
	if (cmd)
		str = cmd->args[1];
	else
		str = NULL;
	while (str && str[i] && ft_isdigit(str[i]))
		i++;
	ft_putstr_fd("exit\n", 1);
	if (str && str[i] == '\0')
		status = ft_atoi(str);
	else if (str)
	{
		print_error("exit", str, "numeric argument required");
		status = 2;
	}
	close_cmd_fds(shell->cmds);
	ft_clean_shell(shell);
	free_env(shell->env);
	free(shell);
	clear_history();
	exit(status);
}
/* //echo
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

/* pwd
int main()
{
	ft_pwd();
}
*/

/* ft_env
int main(int argc, char **argv, char **envp)
{
	// Testa a função ft_env com o envp passado pelo sistema
	(void)argc;
	(void)argv;
	ft_env(envp);

	return 0;
}
*/
/* // cd
int main(int argc, char **argv, char **envp)
{
    if (argc > 1)
        ft_cd(argv, envp);
    else
    {
        char *no_args[] = { "cd", NULL };
        ft_cd(no_args, envp);
    }

    // Agora imprime o diretório atual para você conferir
	ft_pwd();
    return 0;
}*/

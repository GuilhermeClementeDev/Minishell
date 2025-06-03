/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:38:02 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/02 21:28:30 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}

void	sigint_exec_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	ft_signals_child(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
		{
			write(2, "Quit (core dumped)\n", 19);
			g_status = 128 + sig;
		}
		if (sig == SIGINT)
			g_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else
		g_status = 1;
}

void	ft_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

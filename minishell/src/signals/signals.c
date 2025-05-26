/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:38:02 by guclemen          #+#    #+#             */
/*   Updated: 2025/05/26 20:19:32 by guclemen         ###   ########.fr       */
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
}
void	ft_signals_child(int status, t_shell *shell)
{
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGQUIT)
		{
			write(2, "Quit (core dumped)\n", 19);
			shell->status = 128 + sig;
		}
		if (sig == SIGINT)
			shell->status = 128 + sig;
	}
	else if (WIFEXITED(status))
		shell->status = WEXITSTATUS(status);
	else
		shell->status = 1;
}
void	ft_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

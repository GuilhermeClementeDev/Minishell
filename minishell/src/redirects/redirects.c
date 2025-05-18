/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:39:19 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/18 01:05:48 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_pipes(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		pipefd[2];

	cmd = cmd_list;
	while (cmd && cmd->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return (-1);
		}
		if (cmd->fd_out == STDOUT_FILENO)
			cmd->fd_out = pipefd[1];
		else
			close(pipefd[1]);
		if (cmd->next->fd_in == STDIN_FILENO)
			cmd->next->fd_in = pipefd[0];
		else
			close(pipefd[0]);
		cmd = cmd->next;
	}
	return (0);
}

char *create_heredoc_file(char *delimiter)
{
	char	*line;
	char	*filename;
	int		fd;

	// Usando /tmp/minishell_heredoc_tmp como exemplo para arquivo temporário
	// Para maior segurança, pode-se usar mkstemp para gerar nomes únicos
	filename = ft_strdup("/tmp/minishell_heredoc_tmp");
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open heredoc tmp");
		return (NULL);
	}

	// Lê as linhas até o delimitador
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (filename);
}

// Processa os heredocs, cria os arquivos temporários e atualiza redir->filename
void	process_heredocs(t_cmd *cmd_list)
{
	t_cmd		*cmd;
	t_redirect	*redir;
	char		*tmp_file;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				tmp_file = create_heredoc_file(redir->filename);
				if (!tmp_file)
				{
					cmd->redirect_error = 1;
					return ;
				}
				if (redir->filename)
					free(redir->filename);
				redir->filename = tmp_file;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

// Aplica os redirecionamentos, ajustando fds para cada comando
int apply_redirects_to_fds(t_cmd *cmd)
{
	t_redirect	*redir;
	int			fd;
	int			error;

	error = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == T_RED_IN)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == T_RED_OUT)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == T_APPEND)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == T_HEREDOC)
			fd = open(redir->filename, O_RDONLY);
		else
		{
			redir = redir->next;
			continue ;
		}
		if (fd < 0)
		{
			perror(redir->filename);
			error = 1;
		}
		else
		{
			if (redir->type == T_RED_IN || redir->type == T_HEREDOC)
			{
				if (cmd->fd_in != STDIN_FILENO)
					close(cmd->fd_in);
				cmd->fd_in = fd;
			}
			else
			{
				if (cmd->fd_out != STDOUT_FILENO)
					close(cmd->fd_out);
				cmd->fd_out = fd;
			}
		}
		redir = redir->next;
	}
	cmd->redirect_error = error;
	return (error);
}

int	apply_redirects_to_all(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		ret;

	ret = 0;
	cmd = cmd_list;
	while (cmd)
	{
		if (apply_redirects_to_fds(cmd))
			ret = -1;
		cmd = cmd->next;
	}
	return (ret);
}

int	prepare_execution(t_cmd *cmd_list)
{
	if (apply_redirects_to_all(cmd_list) == -1)
	{
		ft_putstr_fd("Error: failed to apply redirects\n", 2);
		return (0);
	}
	if (setup_pipes(cmd_list) == -1)
	{
		ft_putstr_fd("Error: failed to create pipes\n", 2);
		return (0);
	}
	return (1);
}

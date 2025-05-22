/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:31:49 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/21 16:00:10 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_heredoc_file(char **filename)
{
	*filename = ft_strdup("/tmp/minishell_heredoc_tmp");
	if (!*filename)
		return (0);
	return (open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
}

static int	write_line_to_file(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (1);
}

char	*create_heredoc_file(char *delimiter)
{
	char	*line;
	char	*filename;
	int		fd;

	fd = open_heredoc_file(&filename);
	if (fd < 0)
	{
		perror("open heredoc tmp");
		return (NULL);
	}
	while (TRUE)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_line_to_file(fd, line);
		free(line);
	}
	close(fd);
	return (filename);
}

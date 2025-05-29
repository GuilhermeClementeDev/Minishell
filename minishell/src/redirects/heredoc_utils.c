/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:31:49 by bieldojt          #+#    #+#             */
/*   Updated: 2025/05/29 11:13:31 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_heredoc_file(char **filename , int *count_heredocs)
{
	char	*tmp_count;
	char	*tmp_filename;

	tmp_count = ft_itoa(*count_heredocs);
	tmp_filename = ft_strdup("/tmp/minishell_heredoc_tmp");
	*filename = ft_strjoin(tmp_filename, tmp_count);
	if (!*filename)
	{
		free(tmp_count);
		free(tmp_filename);
		return (0);
	}
	free(tmp_count);
	free(tmp_filename);
	(*count_heredocs)++;
	return (open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
}

static int	write_line_to_file(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (1);
}

char	*create_heredoc_file(char *delimiter, int *count_heredocs)
{
	char	*line;
	char	*filename;
	int		fd;

	fd = open_heredoc_file(&filename, count_heredocs);
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

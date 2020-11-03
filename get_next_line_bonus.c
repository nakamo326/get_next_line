/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:55:15 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/03 16:03:44 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_all(char **buf)
{
	int	i;

	i = 0;
	while (i < FD_MAX)
		free(buf[i++]);
}

ssize_t	process_buf(char **line, char **buf)
{
	char	*tmp;
	char	*ptr;

	if (!(ptr = ft_strchr(*buf, '\n')))
		return (CONTINUE);
	if (!(tmp = ft_strdup(ptr + 1)))
		return (ERROR);
	if ((ptr = ft_strchr(tmp, '\n')))
	{
		SAFE_FREE(*line);
		if (!(*line = ft_substr(tmp, 0, ptr - tmp)))
			return (ERROR);
		SAFE_FREE(*buf);
		if (!(*buf = ft_substr(tmp, ptr - tmp, ft_strlen(tmp))))
			return (ERROR);
		SAFE_FREE(tmp);
		return (SUCCESS);
	}
	SAFE_FREE(*line);
	*line = tmp;
	return (CONTINUE);
}

ssize_t	creat_line(char **line, char **buf)
{
	char *tmp;
	char *ptr;

	if ((ptr = ft_strchr(*buf, '\n')))
	{
		if (!(tmp = ft_substr(*buf, 0, ptr - *buf)))
			return (ERROR);
		ptr = *line;
		if (!(*line = ft_strjoin(*line, tmp)))
			return (ERROR);
		SAFE_FREE(tmp);
		SAFE_FREE(ptr);
		return (SUCCESS);
	}
	ptr = *line;
	if (!(*line = ft_strjoin(*line, *buf)))
		return (ERROR);
	SAFE_FREE(ptr);
	return (CONTINUE);
}

ssize_t	read_line(ssize_t fd, char **line, char **buf)
{
	ssize_t rc;
	ssize_t ret;

	while ((rc = read(fd, *buf, BUFFER_SIZE)))
	{
		if (rc == -1)
			return (ERROR);
		(*buf)[rc] = '\0';
		ret = creat_line(line, buf);
		if (ret == -1)
			return (ERROR);
		if (ret == 1)
			return (SUCCESS);
	}
	return (END);
}

int		get_next_line(int fd, char **line)
{
	static char	*buf[FD_MAX];
	ssize_t		ret;

	if (fd < 0 || fd > FD_MAX || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	if (read(fd, buf[fd], 0) < 0)
		return (ERROR);
	if (!(*line = ft_strdup("")))
		return (ERROR);
	ret = process_buf(line, &buf[fd]);
	if (ret == CONTINUE)
	{
		SAFE_FREE(buf[fd]);
		if (!(buf[fd] = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		{
			free_all(buf);
			return (ERROR);
		}
		ret = read_line(fd, line, &buf[fd]);
	}
	if (ret == -1 || ret == 1)
		return (ret);
	SAFE_FREE(buf[fd]);
	return (END);
}

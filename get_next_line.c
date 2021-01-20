/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:55:15 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/20 10:18:22 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	safe_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
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
		safe_free(line);
		if (!(*line = ft_substr(tmp, 0, ptr - tmp)))
			return (ERROR);
		safe_free(buf);
		if (!(*buf = ft_substr(tmp, ptr - tmp, ft_strlen(tmp))))
			return (ERROR);
		safe_free(&tmp);
		return (SUCCESS);
	}
	safe_free(line);
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
		safe_free(&tmp);
		safe_free(&ptr);
		return (SUCCESS);
	}
	ptr = *line;
	if (!(*line = ft_strjoin(*line, *buf)))
		return (ERROR);
	safe_free(&ptr);
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
		if (ret == ERROR || ret == SUCCESS)
			return (ret);
	}
	return (END);
}

int		get_next_line(int fd, char **line)
{
	static char	*buf;
	ssize_t		ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (ERROR);
	if (!(*line = ft_strdup("")))
		return (ERROR);
	ret = process_buf(line, &buf);
	if (ret == CONTINUE)
	{
		safe_free(&buf);
		if (!(buf = malloc(sizeof(char) * BUFFER_SIZE + 1)))
			return (ERROR);
		ret = read_line(fd, line, &buf);
	}
	if (ret == ERROR || ret == SUCCESS)
		return (ret);
	safe_free(&buf);
	return (END);
}

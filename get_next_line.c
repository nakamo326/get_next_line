/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:55:15 by ynakamot          #+#    #+#             */
/*   Updated: 2021/04/21 09:00:12 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	safe_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static ssize_t	process_buf(char **line, char **buf)
{
	char	*tmp;
	char	*ptr;

	ptr = ft_strchr(*buf, '\n');
	if (ptr == NULL)
		return (CONTINUE);
	*line = ft_strdup(ptr + 1);
	if (*line == NULL)
		return (ERROR);
	ptr = ft_strchr(*line, '\n');
	if (ptr == NULL)
		return (CONTINUE);
	tmp = *line;
	*line = ft_substr(tmp, 0, ptr - tmp);
	if (*line == NULL)
		return (ERROR);
	safe_free(buf);
	*buf = ft_substr(tmp, ptr - tmp, ft_strlen(tmp));
	if (*buf == NULL)
		return (ERROR);
	safe_free(&tmp);
	return (SUCCESS);
}

static ssize_t	creat_line(char **line, char **buf)
{
	char	*tmp;
	char	*ptr;

	ptr = ft_strchr(*buf, '\n');
	if (ptr)
	{
		tmp = ft_substr(*buf, 0, ptr - *buf);
		if (tmp == NULL)
			return (ERROR);
		ptr = *line;
		*line = ft_strjoin(*line, tmp);
		if (*line == NULL)
			return (ERROR);
		safe_free(&tmp);
		safe_free(&ptr);
		return (SUCCESS);
	}
	ptr = *line;
	*line = ft_strjoin(*line, *buf);
	if (*line == NULL)
		return (ERROR);
	safe_free(&ptr);
	return (CONTINUE);
}

static ssize_t	read_line(ssize_t fd, char **line, char **buf)
{
	ssize_t	rc;
	ssize_t	ret;

	ret = CONTINUE;
	while (ret == CONTINUE)
	{
		rc = read(fd, *buf, BUFFER_SIZE);
		if (rc == 0)
			break ;
		if (rc == -1)
			return (ERROR);
		(*buf)[rc] = '\0';
		ret = creat_line(line, buf);
		if (ret == ERROR || ret == SUCCESS)
			return (ret);
	}
	return (END);
}

int	get_next_line(int fd, char **line)
{
	static char	*buf = NULL;
	ssize_t		ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (ERROR);
	*line = NULL;
	ret = process_buf(line, &buf);
	if (ret == CONTINUE)
	{
		safe_free(&buf);
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return (ERROR);
		ret = read_line(fd, line, &buf);
	}
	if (ret == ERROR || ret == SUCCESS)
		return (ret);
	safe_free(&buf);
	return (END);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanuel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:32:33 by fmanuel-          #+#    #+#             */
/*   Updated: 2021/10/29 17:17:23 by fmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	ssize_t	read_buffer(int fd, char *buffer)
{
	ssize_t	n;

	n = read(fd, buffer, BUFFER_SIZE);
	if (n >= 0)
	{
		buffer[n] = '\0';
	}
	return (n);
}

static	int	init(int fd, t_filebuffer *filebuf, char **line, size_t *line_sz)
{
	if (fd < 0)
		return (0);
	if (fd != filebuf->fd)
	{
		filebuf->fd = fd;
		filebuf->buffer[0] = '\0';
	}
	if (filebuf->buffer[0] == '\0' || filebuf->pos[0] == '\0')
	{
		if (read_buffer(fd, filebuf->buffer) <= 0)
			return (0);
		filebuf->pos = filebuf->buffer;
	}
	*line_sz = 0;
	*line = malloc(*line_sz + 1);
	if (!(*line))
		return (0);
	*line [0] = '\0';
	return (1);
}

static int	get_line(t_filebuffer *fbuf, char **newpos, char **line, size_t *sz)
{
	int	nchars;

	if (*newpos)
		nchars = *newpos - fbuf->pos + 1;
	else
		nchars = ft_strlen(fbuf->pos);
	*line = ft_realloc(*line, *sz + 1, *sz + nchars + 1);
	if (!line)
		return (0);
	ft_memmove(*line + *sz, fbuf->pos, nchars);
	*sz = (*sz) + nchars;
	(*line)[*sz] = '\0';
	if (*newpos)
		fbuf->pos = ++(*newpos);
	else
		fbuf->pos = fbuf->buffer;
	return (1);
}

char	*get_next_line(int fd)
{
	static t_filebuffer	filebuf = {-1, "", 0};
	ssize_t				nchars_read;
	char				*newpos;
	char				*line;
	size_t				line_sz;

	if (!init(fd, &filebuf, &line, &line_sz))
		return (NULL);
	while (filebuf.buffer[0])
	{
		newpos = ft_strchr(filebuf.pos, '\n');
		if (!get_line(&filebuf, &newpos, &line, &line_sz))
			return (NULL);
		if (newpos)
			return (line);
		nchars_read = read_buffer(fd, filebuf.buffer);
		if (nchars_read < 0)
			return (NULL);
	}
	if (line_sz != 0)
		return (line);
	else
		return (NULL);
}

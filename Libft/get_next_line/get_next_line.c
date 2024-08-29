/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:03:26 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/13 04:57:30 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check(char **line)
{
	int	i;

	if (!(*line))
		return (-1);
	i = ft_strlen_gnl(*line, '\n');
	if ((*line)[i] == '\n')
		return (i);
	return (-1);
}

char	*update_line(char **line, int size)
{
	char	*buf;
	char	*temp;
	int		i;

	buf = ft_joindup(NULL, *line, size + 1, 0);
	i = ft_strlen_gnl(*line, '\0');
	if (i < size + 1)
		size--;
	temp = ft_joindup(*line + size + 1, NULL, 0, 0);
	free(*line);
	*line = temp;
	return (buf);
}

int	initialize_line(int fd, char **line, char **buf)
{
	int	res;

	if (BUFFER_SIZE <= 0 || (fd < 0 || fd > 1000))
	{
		*buf = NULL;
		return (1);
	}
	res = check(line);
	if (res != -1)
	{
		if (*buf)
			free(*buf);
		*buf = update_line(line, res);
		return (1);
	}
	return (0);
}

int	read_and_process(int fd, char **line, char **buf, int *ret)
{
	while (*ret > 0 || *ret == -10)
	{
		if (*ret != -10)
		{
			(*buf)[*ret] = '\0';
			*line = ft_joindup(*line, *buf, ft_strlen_gnl(*buf, '\0'), 1);
		}
		if (check(buf) != -1 || *ret != BUFFER_SIZE)
		{
			if (*buf)
				free(*buf);
			*buf = get_next_line(fd);
			return (1);
		}
		else
		{
			*ret = read(fd, *buf, BUFFER_SIZE);
			if (*ret == 0)
				*ret = -10;
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*line[1000];
	char		*buf;
	int			ret;

	buf = NULL;
	ret = initialize_line(fd, &(line[fd]), &buf);
	if (ret == 1)
		return (buf);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == 0 && line[fd] && (*line[fd]) != '\0')
		return (free(buf), update_line(&(line[fd]),
				ft_strlen_gnl(line[fd], '\n')));
	if (ret == -1)
	{
		free(buf);
		free(line[fd]);
		return (NULL);
	}
	if (read_and_process(fd, &(line[fd]), &buf, &ret))
		return (buf);
	free(buf);
	return (NULL);
}

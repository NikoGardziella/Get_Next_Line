/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:28:28 by ngardzie          #+#    #+#             */
/*   Updated: 2022/01/10 15:26:41 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_check_saved(char **saved, char **line, const int fd)
{
	char	*temp;

	temp = NULL;
	if (saved[fd])
	{
		if (ft_strchr(saved[fd], '\n'))
		{
			temp = ft_strchr(saved[fd], '\n');
			*temp = '\0';
			*line = ft_strdup(saved[fd]);
			temp++;
			ft_strcpy(saved[fd], temp);
		}
		else
		{
			*line = ft_strdup(saved[fd]);
			ft_strdel(&saved[fd]);
		}
	}
	else
		*line = ft_strnew(0);
	return (temp);
}

static char	*ft_join_and_free(char **line, char *buf)
{
	char	*joined;

	joined = ft_strjoin(*line, buf);
	ft_strdel(line);
	return (joined);
}

static int	ft_last_check(int bytes_read, char **line)
{
	if (bytes_read != 0)
		return (1);
	else
	{
		if (ft_strlen(*line) > 0)
			return (1);
		ft_strdel(line);
		return (0);
	}
}

static int	ft_read_line(const int fd, char **line, char *saved[])
{
	char		buf[BUFF_SIZE + 1];
	int			bytes_read;
	char		*temp;

	temp = ft_check_saved(saved, line, fd);
	bytes_read = 1;
	while (temp == NULL && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFF_SIZE);
		buf[bytes_read] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			printf("temp: %s\n", temp);
			temp = ft_strchr(buf, '\n');
			printf("temp: %s\n", temp);
			*temp = '\0';
			printf("temp: %s\n", temp);
			ft_strdel(&saved[fd]);
			printf("temp: %s\n", temp);
			saved[fd] = ft_strdup(++temp);
			printf("temp: %s\n", temp);
		}
		*line = ft_join_and_free(line, buf);
	}
	return (ft_last_check(bytes_read, line));
}

int	get_next_line(const int fd, char **line)
{
	static char	*saved[FD_SIZE];

	if (read(fd, saved[0], 0) < 0)
		return (-1);
	if (fd < 0 || fd >= FD_SIZE || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	return (ft_read_line(fd, line, saved));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:51:18 by mtuomine          #+#    #+#             */
/*   Updated: 2019/10/24 11:44:35 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	handle_line(const int fd, char **curr, char **line)
{
	size_t	len;
	char	*offset;

	len = 0;
	while (curr[fd][len] != '\n' && curr[fd][len] != '\0')
		len++;
	if (curr[fd][len] == '\n')
	{
		*line = ft_strsub(curr[fd], 0, len);
		offset = ft_strdup(curr[fd] + len + 1);
		free(curr[fd]);
		curr[fd] = offset;
		if (curr[fd][0] == '\0')
			ft_strdel(&curr[fd]);
	}
	else
	{
		*line = ft_strdup(curr[fd]);
		ft_strdel(&curr[fd]);
	}
	return (1);
}

static int	handle_return(const int fd, int bytes, char **curr, char **line)
{
	if (bytes < 0)
		return (-1);
	else if (bytes == 0 && curr[fd] == NULL)
		return (0);
	else
		return (handle_line(fd, curr, line));
}

int			get_next_line(const int fd, char **line)
{
	int			bytes;
	char		buf[BUFF_SIZE + 1];
	static char	*curr[MAX_FD];
	char		*temp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((bytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if (curr[fd] == NULL)
			curr[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(curr[fd], buf);
			free(curr[fd]);
			curr[fd] = temp;
		}
		if (ft_strchr(curr[fd], '\n'))
			break ;
	}
	return (handle_return(fd, bytes, curr, line));
}

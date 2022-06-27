/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolaso-u <nolaso-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:54:32 by nolaso-u          #+#    #+#             */
/*   Updated: 2022/06/27 16:58:40 by nolaso-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *static_buf)
{
	int		i;
	char	*final_line;

	i = 0;
	if (!static_buf[i])
		return (NULL);
	while (static_buf[i] && static_buf[i] != '\n')
	i++;
	final_line = malloc(sizeof(char) * ft_strlen(static_buf) + 1);
	if (final_line == NULL)
		return (NULL);
	i = 0;
	while (static_buf[i] && static_buf[i] != '\n')
	{
		final_line[i] = static_buf[i];
		i++;
	}
	if (static_buf[i] == '\n')
	{
		final_line[i] = static_buf [i];
		i++;
	}
	final_line[i] = '\0';
	return (final_line);
}

char	*ft_get_static_buf(char *static_buf)
{
	char	*final_line;
	int		i;
	int		k;

	i = 0;
	while (static_buf[i] && static_buf[i] != '\n')
		i++;
	if (!static_buf[i])
		return (free(static_buf), NULL);
	final_line = malloc(sizeof(char) * ft_strlen(static_buf) - i + 1);
	if (!final_line)
		return (NULL);
	i++;
	k = 0;
	while (static_buf[i])
		final_line[k++] = static_buf[i++];
	final_line[k] = '\0';
	free(static_buf);
	return (final_line);
}

char	*get_next_line(int fd)
{
	static char	*static_buf;
	char		*buffer;
	char		*line;
	int			read_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_line = 1;
	while ((ft_strchr(static_buf, '\n') == NULL) && read_line != 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line < 0)
			return (free(buffer), NULL);
		buffer[read_line] = '\0';
		static_buf = ft_strjoin(static_buf, buffer);
	}
	free(buffer);
	line = ft_get_line(static_buf);
	static_buf = ft_get_static_buf(static_buf);
	return (line);
}

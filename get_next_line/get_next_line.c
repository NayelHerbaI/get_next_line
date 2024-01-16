/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naherbal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:02:39 by naherbal          #+#    #+#             */
/*   Updated: 2023/05/31 14:49:07 by naherbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_buffer(int fd, char *buffer)
{
	char	tmp[BUFFER_SIZE + 1];
	int		nb;
	char	*old;

	nb = 1;
	tmp[0] = '\0';
	while (!ft_strchr(tmp, '\n') && nb > 0)
	{
		nb = read(fd, tmp, BUFFER_SIZE);
		if (nb < 0)
			return (NULL);
		if (nb > 0)
		{
			tmp[nb] = '\0';
			old = buffer;
			buffer = ft_strjoin(buffer, tmp);
			free(old);
		}
	}
	return (buffer);
}

char	*fill_line(char *buffer)
{
	int		size;
	char	*tmp;

	tmp = ft_strchr(buffer, '\n');
	size = (tmp - buffer) + 1;
	tmp = ft_substr(buffer, 0, size);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*delete_line(char *buffer)
{
	char	*tmp;
	int		size;
	int		buffer_len;

	buffer_len = ft_strlen(buffer);
	tmp = ft_strchr(buffer, '\n');
	if (!tmp)
		return (NULL);
	size = (tmp - buffer) + 1;
	if (!buffer[size])
		return (NULL);
	tmp = ft_substr(buffer, size, buffer_len - size);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buffer)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!buffer || (buffer && !ft_strchr(buffer, '\n')))
			buffer = fill_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = fill_line(buffer);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	tmp = delete_line(buffer);
	free(buffer);
	buffer = tmp;
	return (line);
}

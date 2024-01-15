/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:24:35 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:25:48 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*read_and_store(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	read_bytes = 1;
	while (!ft_search(save, '\n') && read_bytes != 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	return (save);
}

char	*the_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*the_saver(char *save)
{
	int		i;
	int		c;
	char	*str;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = malloc(sizeof(char) * ((ft_strlen(save) - i) + 1));
	if (!str)
		return (NULL);
	i++;
	c = 0;
	while (save[i])
		str[c++] = save[i++];
	str[c] = '\0';
	free(save);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	char		*temp;

	line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	temp = read_and_store(fd, save);
	if (!temp)
	{
		if (save)
			free(save);
		save = NULL;
		return (NULL);
	}
	save = temp;
	if (save)
		line = the_line(save);
	save = the_saver(save);
	return (line);
}

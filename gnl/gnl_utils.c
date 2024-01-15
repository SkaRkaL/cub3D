/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:24:32 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/15 19:29:26 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		y;
	char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	y = ft_strlen((char *)s);
	ptr = malloc((y + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *save, char *buff)
{
	char	*str;
	int		total;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!save && !buff)
		return (0);
	if (!save)
		save = ft_strdup("");
	total = ft_strlen(save) + ft_strlen(buff);
	str = (char *)malloc(sizeof(char) * (total + 1));
	if (!str)
		return (NULL);
	while (save[++i] != '\0')
		str[i] = save[i];
	while (buff[++j] != '\0')
		str[i + j] = buff[j];
	str[i + j] = '\0';
	free(save);
	free(buff);
	return (str);
}

char	*ft_search(char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (0);
}

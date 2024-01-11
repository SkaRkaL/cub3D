/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:05:47 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/11 17:06:06 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strtok(char *str, char *sep)
{
	static char	*rem;
	char		*ret;
	int			length;

	if (str)
		rem = str;
	if (!rem)
		return (NULL);
	while (*rem && ft_strchr(sep, *rem))
		rem++;
	length = 0;
	while (rem[length] && !ft_strchr(sep, rem[length]))
		length++;
	if (!length)
		return (NULL);
	ret = ft_substr(rem, 0, length);
	rem += length;
	while (*rem && ft_strchr(sep, *rem))
		rem++;
	return (ret);
}

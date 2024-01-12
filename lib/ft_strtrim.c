/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:59:54 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 01:48:57 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;
	int	x;

	x = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (x);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	if (!len || start >= ft_strlen(s))
		return (ft_strdup(""));
	i = ft_strlen(s) - start;
	if (i > len)
		i = len;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s + start, i + 1);
	return (str);
}

static char	*ft_sdup(const char *s)
{
	int		i;
	int		y;
	char	*ptr;

	i = 0;
	y = ft_strlen(s);
	ptr = malloc(y + 1 * sizeof(char));
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

char	*ft_strtrim(char const *s, char const *set)
{
	int		strt;
	int		end;
	char	*ptr;

	strt = 0;
	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
		return (ft_sdup(""));
	if (set == NULL)
		return (ft_sdup(s));
	while (ft_strchr(set, s[strt]) && s[strt])
		strt++;
	end = ft_strlen(s);
	while (ft_strchr(set, s[end]) && end != 0)
		end--;
	if (end < strt)
		return (ft_sdup(""));
	ptr = ft_substr(s, strt, end - strt + 1);
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repeat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:24:19 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 20:22:30 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_repeat(char c, size_t a)
{
	size_t	i;
	char	*s;

	s = malloc((a + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (i < a)
	{
		s[i] = c;
		i++;
	}
	s[a] = '\0';
	return (s);
}

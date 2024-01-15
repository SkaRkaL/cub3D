/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:25 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 20:24:19 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	invalid_number(char *str)
{
	int	i;
	int	start_number;

	i = 0;
	while (str[i] == '0')
		i++;
	start_number = i;
	while (str[i])
	{
		if (*(str + i) < '0' || *(str + i) > '9')
			return (0);
		i++;
	}
	if (i - start_number > 3)
		return (0);
	return (1);
}

int	check_commas(char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicated.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:22:58 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:22:59 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_duplicates(short flag, short full_flag)
{
	static char		*kk[6] = {"NO", "SO", "WE", "EA", "C", "F"};
	static short	kk_flag[6] = {1, 2, 4, 8, 16, 32};
	int				i;

	if (flag != full_flag)
	{
		i = 0;
		while (i < 6)
		{
			if (!(flag & kk_flag[i]))
				printf("missing [ %s ] key \n", kk[i]);
			i++;
		}
		exit_err("Error\nMissing key");
	}
}

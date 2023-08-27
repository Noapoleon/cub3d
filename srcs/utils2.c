/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:10:09 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/26 19:18:40 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Clears all the pixels of the image buffer to the specified color
void	clear_img(t_cub *cub, int col)
{
	// move in subfolder for graphics things later
	// replace with function that clears with ceiling and floor colors
	int		x;
	int		y;

	y = 0;
	while (y < cub->mlx.h)
	{
		x = 0;
		while (x < cub->mlx.w)
		{
			my_pixel_put(cub, (int[2]){x, y}, col);
			++x;
		}
		++y;
	}
}

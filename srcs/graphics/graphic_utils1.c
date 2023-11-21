/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:21:17 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 19:51:56 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Clears all the pixels of the image buffer to the specified color
void	clear_imgmlx(t_cub *cub, int col)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->mlx.h)
	{
		x = 0;
		while (x < cub->mlx.w)
		{
			set_pixel(&cub->mlx.img, (int [2]){x, y}, col);
			++x;
		}
		++y;
	}
}

// Copies pixels of src to dst at pos in dst
void	copy_imgmlx(t_imgmlx *src, t_imgmlx *dst, int pos[2])
{
	int	coord[2];
	int	cur[2];

	coord[1] = 0;
	while (coord[1] < src->h)
	{
		coord[0] = 0;
		while (coord[0] < src->w)
		{
			cur[0] = pos[0] + coord[0];
			cur[1] = pos[1] + coord[1];
			set_pixel(dst, cur, get_pixel(src, coord));
			++(coord[0]);
		}
		++(coord[1]);
	}
}

// Substitute function for mlx_pixel_put
// Writes pixels into the image buffer instead of directly to the screen for
// much better performance
void	set_pixel(t_imgmlx *img, int pos[2], int col)
{
	char	*dst;

	if (pos[0] >= 0 && pos[0] < img->w
		&& pos[1] >= 0 && pos[1] < img->h)
	{
		dst = img->addr + (pos[1] * img->ll + pos[0] * (img->bpp / 8));
		*(unsigned int *)dst = col;
	}
}

// Get color of pixel in imgmlx at coords pos
int	get_pixel(t_imgmlx *img, int pos[2])
{
	char	*dst;

	if (pos[0] >= 0 && pos[0] < img->w
		&& pos[1] >= 0 && pos[1] < img->h)
	{
		dst = img->addr + (pos[1] * img->ll + pos[0] * (img->bpp / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

// Draws rectangle to imgmlx
void	set_rect(t_imgmlx *img, int pos[2], int size[2], int col)
{
	int	x;
	int	y;

	if (size[0] < 0 || size[1] < 0)
		return ;
	y = 0;
	while (y < size[1])
	{
		x = 0;
		while (x < size[0])
			set_pixel(img, (int [2]){pos[0] + x++, pos[1] + y}, col);
		++y;
	}
}

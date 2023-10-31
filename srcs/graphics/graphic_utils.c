/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:21:17 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/31 17:29:59 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns the color of pixel in the texture at coordinates pos
// Returns 0 if outside of texture range
int	get_tex_col(t_texture *t, int pos[2])
{
	char	*dst;

	if (pos[0] >= 0 && pos[0] < t->w
			&& pos[1] >= 0 && pos[1] < t->h)
	{
		dst = t->img.addr + (pos[1] * t->img.ll + pos[0] * (t->img.bpp / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

// Substitute function for mlx_pixel_put
// Writes pixels into the image buffer instead of directly to the screen for
// much better performance
void	my_pixel_put(t_mlx *m, int pos[2], int col)
{
	char	*dst;

	if (pos[0] >= 0 && pos[0] < m->w
			&& pos[1] >= 0 && pos[1] < m->h)
	{
		dst = m->img.addr + (pos[1] * m->img.ll + pos[0] * (m->img.bpp / 8));
		*(unsigned int *)dst = col;
	}
}

// draws rectangle to imgbuf
void	my_rect_put(t_mlx *m, int pos[2], int size[2], int col)
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
			my_pixel_put(m, (int[2]){pos[0] + x++, pos[1] + y}, col);
		++y;
	}
}

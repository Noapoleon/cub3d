/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:21:17 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/19 18:38:54 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Opens single texture file and fills in texture struct with info
int	open_texture(t_mlx *mlx, t_texture *t)
{
	if (t->path == NULL)
		return (-1);
	t->img.ptr = mlx_xpm_file_to_image(mlx->ptr, t->path, &t->w, &t->h);
	if (t->img.ptr == NULL)
		return (-1);
	t->img.addr = mlx_get_data_addr(t->img.ptr, &t->img.bpp, &t->img.ll,
			&t->img.endian);
	return (0);
}

// Substitute function for mlx_pixel_put
// Writes pixels into the image buffer instead of directly to the screen for
// much better performance
void	set_pixel(t_mlximg *img, int pos[2], int col)
{
	char	*dst;

	if (pos[0] >= 0 && pos[0] < img->w
			&& pos[1] >= 0 && pos[1] < img->h)
	{
		dst = img->addr + (pos[1] * img->ll + pos[0] * (img->bpp / 8));
		*(unsigned int *)dst = col;
	}
}

// Get color of pixel in mlximg at coords pos
int	get_pixel(t_mlximg *img, int pos[2])
{
	char	*dst;

	if (pos[0] >= 0 && pos[0] < img->w
			&& pos[1] >= 0 && pos[1] < img->h)
	{
		dst = img->addr + (pos[1] * img->ll + pos[0] * (img->bpp / 8));
		return (*(unsigned int *)dst);
	}
}

// draws rectangle to mlximg
void	set_rect(t_mlximg *img, int pos[2], int size[2], int col)
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
			set_pixel(img, (int[2]){pos[0] + x++, pos[1] + y}, col);
		++y;
	}
}

// Draws texture to buffer at native resolution
void	my_texture_put(t_mlx *mlx, int pos[2], t_texture *t) // probably remove
{
	int	coord[2];
	int	cur[2];

	coord[1] = 0;
	while (coord[1] < t->h)
	{
		coord[0] = 0;
		while (coord[0] < t->w)
		{
			cur[0] = pos[0] + coord[0];
			cur[1] = pos[1] + coord[1];
			set_pixel(mlx->img, cur, get_pixel(&t->img, coord));
			++(coord[0]);
		}
		++(coord[1]);
	}
}


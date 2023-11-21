/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:49:26 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 05:07:24 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// stores image information in imgmlx struct properly in a concise function
void	set_imgmlx_data(t_imgmlx *img, int width, int height)
{
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->ll, &img->endian);
	img->w = width;
	img->h = height;
}

// Copies pixels of src to dst
void	copy_frame(t_imgmlx *src, t_imgmlx *dst, int pos[2])
{
	int	coord[2];
	int	cur[2];

	cur[1] = 0;
	while (cur[1] < dst->h)
	{
		cur[0] = 0;
		while (cur[0] < dst->w)
		{
			coord[0] = pos[0] + cur[0];
			coord[1] = pos[1] + cur[1];
			set_pixel(dst, cur, get_pixel(src, coord));
			++(cur[0]);
		}
		++(cur[1]);
	}
}

// Opens single texture file and fills in texture struct with info
int	open_texture(t_mlx *mlx, t_texture *t)
{
	if (t->path == NULL)
		return (-1);
	t->img.ptr = mlx_xpm_file_to_image(mlx->ptr, t->path, &t->w, &t->h);
	if (t->img.ptr == NULL)
		return (-1);
	set_imgmlx_data(&t->img, t->w, t->h);
	return (0);
}

// Uses delta time for elapsed time and decides when to refresh sprites
void	refresh_sprite(t_cub *cub, t_sprite *s)
{
	s->elapsed += cub->delta;
	if (s->elapsed >= s->delay)
	{
		s->elapsed = 0;
		++(s->index);
		if (s->index == s->num_frames)
			s->index = 0;
		s->frame = &s->frames[s->index];
	}
}

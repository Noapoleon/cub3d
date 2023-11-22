/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:06:44 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/22 14:14:14 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	extract_frame(t_mlx *mlx, t_sprite *s, t_texture *frame, int i)
{
	init_vars_texture(frame);
	frame->img.ptr = mlx_new_image(mlx->ptr, s->tex.h, s->tex.h);
	if (frame->img.ptr == NULL)
		return (ft_perr(CUB_ERR CE_SPRITE_IMG), -1);
	set_imgmlx_data(&frame->img, s->tex.h, s->tex.h);
	frame->w = s->tex.h;
	frame->h = s->tex.h;
	copy_frame(&s->tex.img, &frame->img, (int [2]){i * s->tex.h, 0});
	return (0);
}

// Creates multiple textures from a single sprite sheet
int	open_sprite(t_mlx *mlx, t_sprite *s, int delay)
{
	int	i;

	if (open_texture(mlx, &s->tex) != 0)
		return (ft_perr(CUB_ERR CE_TEX_OPEN, s->tex.path), -1);
	if (s->tex.w % s->tex.h != 0)
		return (ft_perr(CUB_ERR CE_SPRITE_RES), -1);
	s->num_frames = s->tex.w / s->tex.h;
	s->frames = malloc(sizeof(t_texture) * s->num_frames);
	if (s->frames == NULL)
		return (ft_perr(CUB_ERR CE_SPRITE_ALLOC, strerror(errno)), -1);
	s->frame = &s->frames[0];
	s->index = 0;
	s->delay = delay;
	i = 0;
	while (i < s->num_frames)
	{
		if (extract_frame(mlx, s, &s->frames[i], i) != 0)
			return (-1);
		++i;
	}
	return (0);
}

// Blends current texture color with floor color for fog effect
int	tex_apply_fog(int col, int col_f, double fog)
{
	int		r;
	int		g;
	int		b;

	r = ((col >> 16) & 0xff)
		- ((double)(((col >> 16) & 0xff) - ((col_f >> 16) & 0xff)) *fog);
	g = ((col >> 8) & 0xff)
		- ((double)(((col >> 8) & 0xff) - ((col_f >> 8) & 0xff)) *fog);
	b = (col & 0xff) - ((double)((col & 0xff) - (col_f & 0xff)) *fog);
	return ((r << 16) | (g << 8) | b);
}

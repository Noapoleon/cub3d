/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:21:17 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/19 23:10:51 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Clears all the pixels of the image buffer to the specified color
void	clear_imgmlx(t_cub *cub, int col)
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
			set_pixel(&cub->mlx.img, (int[2]){x, y}, col);
			++x;
		}
		++y;
	}
}

void	set_imgmlx_data(t_imgmlx *img, int width, int height)
{
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->ll, &img->endian);
	img->w = width;
	img->h = height;
}


// Copies pixels of src to dst
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

int	open_sprite(t_mlx *mlx, t_sprite *s, int delay)
{
	int	i;

	if (open_texture(mlx, &s->tex) != 0)
		return (-1);
	if (s->tex.w % s->tex.h != 0) // test edge cases
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
		init_vars_texture(&s->frames[i]);
		s->frames[i].img.ptr = mlx_new_image(mlx, s->tex.h, s->tex.h);
		if (s->frames[i].img.ptr == NULL)
			return (ft_perr(CUB_ERR CE_SPRITE_IMG), -1);
		set_imgmlx_data(&s->frames[i].img, s->tex.h, s->tex.h);
		copy_imgmlx(&s->tex.img, &s->frames[i].img, (int[2]){i * s->tex.h, 0});
		++i;
	}
	return (0);
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

// draws rectangle to imgmlx
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
			set_pixel(img, (int[2]){pos[0] + x++, pos[1] + y}, col);
		++y;
	}
}

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

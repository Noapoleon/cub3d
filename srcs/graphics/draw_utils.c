/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:32:27 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/17 18:54:27 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_ray *r, t_player *p, int	index)
{
	double	cam_x;

	r->index = index;
	cam_x = ((2.0 * (double)index) / (double)W_WIDTH) - 1.0;
	set_vec2df(&r->dir, p->dir.x + p->cam.x * cam_x,
			p->dir.y + p->cam.y * cam_x);
	set_vec2df(&r->step_dist, fabs(1.0 / r->dir.x), fabs(1.0 / r->dir.y));
	set_vec2di(&r->map_check, p->pos.x, p->pos.y);
	set_vec2di(&r->step, 1 - (r->dir.x < 0.0) * 2, 1 - (r->dir.y > 0.0) * 2);
	if (r->dir.x < 0.0)
		r->dist.x = (p->pos.x - (double)r->map_check.x) * r->step_dist.x;
	else
		r->dist.x = ((double)(r->map_check.x + 1) - p->pos.x) * r->step_dist.x;
	if (r->dir.y < 0.0)
		r->dist.y = ((double)(r->map_check.y + 1) - p->pos.y) * r->step_dist.y;
	else
		r->dist.y = (p->pos.y - (double)r->map_check.y) * r->step_dist.y;
	r->last_dist = 0.0;
	r->side = -1;
}

static int	ray_hit_detection(t_ray *r, t_cub *cub)
{
	while (r->last_dist <= RENDER_DIST)
	{
		if (r->dist.x < r->dist.y)
		{
			r->map_check.x += r->step.x;
			r->last_dist = r->dist.x;
			r->dist.x += r->step_dist.x;
			r->side = (r->step.x > 0) + 2;
		}
		else
		{
			r->map_check.y += r->step.y;
			r->last_dist = r->dist.y;
			r->dist.y += r->step_dist.y;
			r->side = r->step.y > 0;
		}

		if ((r->map_check.x >= 0 && r->map_check.x < cub->map.w) &&
				(r->map_check.y >= 0 && r->map_check.y < cub->map.h))
		{
			if (cub->map.tiles[r->map_check.y][r->map_check.x])
				return (1);
		}
	}
	return (0);
}

// Prints vertical line with texture
static void	draw_vert_line(t_mlx *mlx, t_props *props, t_ray *r)
{
	int	height;
	//const t_texture *t = cub->props.walls[r->side];
	int	tx_pos[2];
	int	pos[2];

	height = (int)((double)W_HEIGHT / r->last_dist);
	if (height > W_HEIGHT) // remove
		height = W_HEIGHT;
	tx_pos[0] = (double)(W_HEIGHT - height) / 2.0;
	tx_pos[1] = W_HEIGHT - tx_pos[0];
	pos[0] = r->index;
	pos[1] = 0;
	while (pos[1] < W_HEIGHT)
	{
		if (pos[1] < tx_pos[0])
			my_pixel_put(mlx, pos, props->col_c);
		else if (pos[1] > tx_pos[1])
			my_pixel_put(mlx, pos, props->col_f);
		else
		{
			// jsp mdr
			my_pixel_put(mlx, pos, 0x00ff0000);
		}
		++pos[1];
	}
}

// Casts one ray per horizontal pixel of the window and draws the vertical
// texture sprites
static void	cast_rays(t_cub *cub, t_player *p)
{
	static t_ray	ray;

	for (int i = 0; i < W_WIDTH; ++i)
	{
		init_ray(&ray, p, i);
		if (ray_hit_detection(&ray, cub))
			draw_vert_line(&cub->mlx, &cub->props, &ray);
	}
}

// Main draw function
int	draw_frame(t_cub *cub, t_mlx *mlx, t_player *player)
{
	(void)player; // remove
	clear_imgbuf(cub, 0x0);
	//display_inputs(cub, (int[2]){20, 20}); // remove later
	//display_map(cub);
	cast_rays(cub, player);
	//display_movdir(cub, (int[2]){500, 500});
	//display_rot(cub, (int[2]){500, 500}); // remove later
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	//mlx_put_image_to_window(mlx->ptr, mlx->win, cub->props.no.img.ptr, 0, 0);
	return (0);
}

// Substitute function for mlx_pixel_put
// Writes pixels into the image buffer instead of directly to the screen for
// much better performance
void	my_pixel_put(t_mlx *mlx, int pos[2], int col)
{
	char	*dst;

	if (pos[0] >= 0 && pos[0] < mlx->w
			&& pos[1] >= 0 && pos[1] < mlx->h)
	{
		dst = mlx->img.addr +
			(pos[1] * mlx->img.ll + pos[0] * (mlx->img.bpp / 8));
		*(unsigned int *)dst = col;
	}
}

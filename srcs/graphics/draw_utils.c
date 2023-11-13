/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:32:27 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/13 15:32:51 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Sets ray struct variables for DDA loop
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

// Loops on the DDA algorithm, stores info in ray struct
// Returns 1 if a wall is hit, returns 0 otherwise
static int	ray_dda_loop(t_ray *r, t_cub *cub)
{
	if (r->index == cub->mlx.w_mid)
		cub->player.cursor = 0;
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
				(r->map_check.y >= 0 && r->map_check.y < cub->map.h)) // clean this later
			if (cub->map.tiles[r->map_check.y][r->map_check.x])
			{
				if (r->index == cub->mlx.w_mid)
					cub->player.cursor
						= cub->map.tiles[r->map_check.y][r->map_check.x];
				return (1);
			}
	}
	r->side = -1; // check later if setting this here doesn't cause problems
	return (0);
}

// Casts one ray per horizontal pixel of the window and draws textures on walls
static void	cast_rays(t_cub *cub, t_player *p)
{
	static t_ray	ray;
	int				i;

	i = 0;
	while (i < W_WIDTH)
	{
		init_ray(&ray, p, i);
		ray_dda_loop(&ray, cub);
		draw_vert_line(cub, &ray);
		printf("looking at -> %d\n", p->cursor);
		++i;
	}
}

// Draws minimap in corner
static void	draw_minimap(t_mlx *mlx, t_map *map, t_player *p)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (map->tiles[y][x] == T_AIR)
				my_rect_put(mlx, (int[2]){10 + x * 10, 10 + y * 10},
						(int[2]){10, 10}, 0x00ffffff); // remove literal array
			++x;
		}
		++y;
	}
	my_rect_put(mlx,
			(int[2]){10 + p->pos.x * 10.0 - 2, 10 + p->pos.y * 10.0 - 2},
			(int[2]){4, 4}, 0x00ff0000);
}

void draw_clock(t_mlx *mlx, t_cub *cub, t_sprite *clock)
{
	static int	n;
	static long	sum;

	sum += cub->dt;
	if (sum >= clock->uspf)
	{
		++n;
		if (n == clock->n)
			n = 0;
		clock->cur = &clock->frames[n];
		sum = 0;
	}
	my_texture_put(mlx, (int[2]){W_WIDTH - 64, 0}, clock->cur);
}

// Main draw function
void	draw_frame(t_cub *cub, t_mlx *mlx, t_player *player)
{
	clear_imgbuf(cub, 0x0);
	cast_rays(cub, player);
	if (cub->minimap)
		draw_minimap(mlx, &cub->map, player);
	//my_pixel_put(mlx, (int[2]){mlx->w_mid, mlx->h_mid}, 0x00ffffff); // cursor
	//display_inputs(cub, (int[2]){0,0}); // remove
	draw_clock(mlx, cub, &cub->clock); // remoe later
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}

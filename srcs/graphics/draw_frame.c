/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:32:27 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 20:25:21 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Sets ray struct variables for DDA loop
void	init_ray(t_ray *r, t_player *p, int index)
{
	double	cam_x;

	r->index = index;
	cam_x = ((2.0 * (double)index) / (double)W_WIDTH) - 1.0;
	set_vec2df(&r->dir, p->dir.x + p->cam.x * cam_x,
		p->dir.y + p->cam.y * cam_x);
	set_vec2df(&r->step_dist, fabs(1.0 / r->dir.x), fabs(1.0 / r->dir.y));
	set_vec2di(&r->map_check, p->pos.x - (p->pos.x < 0.0),
		p->pos.y - (p->pos.y < 0.0));
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
	r->tile_type = -1;
	r->render_dist = RENDER_DIST;
}

// Loops on the DDA algorithm, stores info in ray struct
// Returns 1 if a wall is hit, returns 0 otherwise
void	ray_dda_loop(t_ray *r, t_cub *cub)
{
	int	*tile;

	if (r->index == cub->mlx.w_mid)
		cub->player.cursor = NULL;
	while (r->last_dist <= r->render_dist)
	{
		dda_increment(r);
		if (r->last_dist >= r->render_dist)
			break ;
		if ((r->map_check.x >= 0 && r->map_check.x < cub->map.w)
			&& (r->map_check.y >= 0 && r->map_check.y < cub->map.h))
		{
			tile = &cub->map.tiles[r->map_check.y][r->map_check.x];
			if (*tile >= T_WALL)
			{
				r->tile_type = *tile;
				if (r->index == cub->mlx.w_mid && r->last_dist <= PLAYER_REACH)
					cub->player.cursor = tile;
				return ;
			}
		}
	}
	r->side = -1;
	r->tile_type = -1;
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
		++i;
	}
}

// Draws minimap in corner
static void	draw_minimap(t_mlx *mlx, t_map *map, t_player *p)
{
	int	x;
	int	y;
	int	pos[2];

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			pos[0] = 10 + (x * 10);
			pos[1] = 10 + (y * 10);
			set_rect(&mlx->img, pos, map->size,
				get_map_color(map->tiles[y][x]));
			++x;
		}
		++y;
	}
	set_rect(&mlx->img,
		(int [2]){10 + p->pos.x * 10.0 - 2, 10 + p->pos.y * 10.0 - 2},
		(int [2]){4, 4}, 0x00ff0000);
}

// Main draw function
void	draw_frame(t_cub *cub, t_mlx *mlx, t_player *player)
{
	clear_imgmlx(cub, 0x0);
	cast_rays(cub, player);
	if (cub->minimap)
		draw_minimap(mlx, &cub->map, player);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:32:27 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/20 16:52:26 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Sets ray struct variables for DDA loop
void	init_ray(t_ray *r, t_player *p, int	index)
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
	r->tile_type = -1;
}

void	dda_increment(t_ray *r)
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
}

// Loops on the DDA algorithm, stores info in ray struct
// Returns 1 if a wall is hit, returns 0 otherwise
int	ray_dda_loop(t_ray *r, t_cub *cub)
{
	int	*tile;

	if (r->index == cub->mlx.w_mid)
		cub->player.cursor = NULL;
	while (r->last_dist <= RENDER_DIST)
	{
		dda_increment(r);
		if ((r->map_check.x >= 0 && r->map_check.x < cub->map.w) &&
				(r->map_check.y >= 0 && r->map_check.y < cub->map.h)) // clean this later
		{
			tile = &cub->map.tiles[r->map_check.y][r->map_check.x];
			if (*tile >= T_WALL) // just added == 1 to test map edge graphic bug
			{
				r->tile_type = *tile;
				if (r->index == cub->mlx.w_mid && r->last_dist <= PLAYER_REACH) // put door loop outside of hit wall for when it's open
					cub->player.cursor = tile;
				return (1);
			}
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
		draw_vert_line(cub, &ray); // modify for different torch and door textures
		//if (p->cursor == NULL)
		//	printf("looking at nothing\n");
		//else
		//	printf("looking at -> %d\n", *(p->cursor));
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
				set_rect(&mlx->img, (int[2]){10 + x * 10, 10 + y * 10},
						(int[2]){10, 10}, 0x00ffffff); // remove literal array
			++x;
		}
		++y;
	}
	set_rect(&mlx->img,
			(int[2]){10 + p->pos.x * 10.0 - 2, 10 + p->pos.y * 10.0 - 2},
			(int[2]){4, 4}, 0x00ff0000);
}

// Main draw function
void	draw_frame(t_cub *cub, t_mlx *mlx, t_player *player)
{
	clear_imgmlx(cub, 0x0);
	cast_rays(cub, player);
	if (cub->minimap)
		draw_minimap(mlx, &cub->map, player);
	//my_pixel_put(mlx, (int[2]){mlx->w_mid, mlx->h_mid}, 0x00ffffff); // cursor
	//display_inputs(cub, (int[2]){0,0}); // remove
	//copy_imgmlx(&cub->props.wall_anim.frame->img, &mlx->img, (int[2]){0,0}); // remove
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}

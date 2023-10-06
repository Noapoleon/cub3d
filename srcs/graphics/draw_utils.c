/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:17:05 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/06 23:04:10 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_rays(t_cub *cub, t_player *p)
{
	double size = 50.0;
	double	ray[2];
	int		step[2];
	double	step_size[2];
	int		tile_check[2];
	double	ray_dist[2];

	// init_ray()
	// ----------
	ray[0] = cos(p->rot);
	ray[1] = sin(p->rot);

	step_size[0] = sqrt(1 + (ray[1] / ray[0]) * (ray[1] / ray[0]));
	step_size[1] = sqrt(1 + (ray[0] / ray[1]) * (ray[0] / ray[1]));

	tile_check[0] = (int)(p->x);
	tile_check[1] = (int)(p->y);

	if (ray[0] < 0.0)
	{
		step[0] = -1;
		ray_dist[0] = (p->x - (double)tile_check[0]) * step_size[0];
	}
	else
	{
		step[0] = 1;
		ray_dist[0] = ((double)(tile_check[0] + 1) - p->x) * step_size[0];
	}
	if (ray[1] < 0.0)
	{
		step[1] = 1;
		ray_dist[1] = ((double)(tile_check[1] + 1) - p->y) * step_size[1];
	}
	else
	{
		step[1] = -1;
		ray_dist[1] = (p->y - (double)tile_check[1]) * step_size[1];
	}
	// ----------
	// init_ray()
	

	int				wall_found;
	const double	max_dist = 100.0;
	double			dist;

	wall_found = 0;
	dist = 0.0;
	while (!wall_found && dist < max_dist)
	{
		if (ray_dist[0] < ray_dist[1])
		{
			tile_check[0] += step[0];
			dist = ray_dist[0];
			ray_dist[0] += step_size[0];
		}
		else
		{
			tile_check[1] += step[1];
			dist = ray_dist[1];
			ray_dist[1] += step_size[1];
		}

		if ((tile_check[0] >= 0 && tile_check[0] < cub->map.w) &&
				(tile_check[1] >= 0 && tile_check[1] < cub->map.h))
		{
			if (cub->map.tiles[tile_check[1]][tile_check[0]])
			{
				//printf("test -> %d:%d\n", tile_check[0], tile_check[1]);
				wall_found = 1;
			}
		}
	}

	if (wall_found)
	{
		//printf("map size -> %d;%d\n", cub->map.w, cub->map.h);
		//printf("tile_check -> %d;%d\n", tile_check[0], tile_check[1]);
		//printf("step -> %d:%d\n", step[0], step[1]);
		int tmp[2];
		tmp[0] = size * (p->x + dist * ray[0]) - 3;
		tmp[1] = size * (p->y - dist * ray[1]) - 3;
		draw_square(cub, tmp, 6, 0x00ff00ff);
		//tmp[0] = size * (p->x + (ray_size[1] + (4.0 * step_size[1])) * ray[0]) - 3;
		//tmp[1] = size * (p->y - (ray_size[1] + (4.0 * step_size[1])) * ray[1]) - 3;
		//draw_square(cub, tmp, 6, 0x00ff00ff);
	}


	(void)ray_dist; // remove
	(void)cub; // remove
	(void)step; // remove
	(void)step_size; // remove
	(void)size; // remove
	//printf("start tile -> %d; %d\n", tile[0], tile[1]);
}

// Main draw function
int	draw_frame(t_cub *cub, t_mlx *mlx, t_player *player)
{
	(void)player; // remove
	clear_imgbuf(cub, 0x0);
	//display_inputs(cub, (int[2]){20, 20}); // remove later
	display_map(cub);
	cast_rays(cub, player);
	//display_movdir(cub, (int[2]){500, 500});
	//display_rot(cub, (int[2]){500, 500}); // remove later
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
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

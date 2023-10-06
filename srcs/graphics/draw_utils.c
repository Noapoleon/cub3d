/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:17:05 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/07 01:10:46 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// init_ray()
	// ----------
	////ray[0] = cos(p->rot);
	////ray[1] = sin(p->rot);

	////step_size[0] = sqrt(1 + (ray[1] / ray[0]) * (ray[1] / ray[0]));
	////step_size[1] = sqrt(1 + (ray[0] / ray[1]) * (ray[0] / ray[1]));

	////ray->map_check[0] = (int)(p->x);
	////ray->map_check[1] = (int)(p->y);

	////if (ray[0] < 0.0)
	////{
	////	step[0] = -1;
	////	ray_dist[0] = (p->x - (double)ray->map_check[0]) * step_size[0];
	////}
	////else
	////{
	////	step[0] = 1;
	////	ray_dist[0] = ((double)(ray->map_check[0] + 1) - p->x) * step_size[0];
	////}
	////if (ray[1] < 0.0)
	////{
	////	step[1] = 1;
	////	ray_dist[1] = ((double)(ray->map_check[1] + 1) - p->y) * step_size[1];
	////}
	////else
	////{
	////	step[1] = -1;
	////	ray_dist[1] = (p->y - (double)ray->map_check[1]) * step_size[1];
	////}
	// ----------
	// init_ray()

typedef struct s_ray	t_ray;
struct s_ray
{
	double	norm[2];
	int		step[2];
	double	step_dist[2];
	int		map_check[2];
	double	dist[2];
	double	prev_dist;
};

static void	init_ray(t_ray *r, t_player *p, double angle)
{
	r->norm[0] = cos(angle);
	r->norm[1] = sin(angle);
	r->step_dist[0] = sqrt(1 + (r->norm[1] / r->norm[0]) *
			(r->norm[1] / r->norm[0]));
	r->step_dist[1] = sqrt(1 + (r->norm[0] / r->norm[1]) *
			(r->norm[0] / r->norm[1]));
	r->map_check[0] = (int)(p->x);
	r->map_check[1] = (int)(p->y);
	r->step[0] = 1 - (r->norm[0] < 0.0) * 2;
	r->step[1] = 1 - (r->norm[1] > 0.0) * 2;
	if (r->norm[0] < 0.0)
		r->dist[0] = (p->x - (double)r->map_check[0]) * r->step_dist[0];
	else
		r->dist[0] = ((double)(r->map_check[0] + 1) - p->x) * r->step_dist[0];
	if (r->norm[1] < 0.0)
		r->dist[1] = ((double)(r->map_check[1] + 1) - p->y) * r->step_dist[1];
	else
		r->dist[1] = (p->y - (double)r->map_check[1]) * r->step_dist[1];
	r->prev_dist = 0.0;
}

static void	cast_rays(t_cub *cub, t_player *p)
{
	static t_ray	ray;
	int				wall_found;

	// refresh_ray() -> loop of different angle rays but same position

	for (int i = 0; i < W_WIDTH; ++i)
	{
		init_ray(&ray, p, p->rot + (((M_PI / 180.0) * 90) / (double)W_WIDTH) * (double)i - (M_PI / 180.0) * 45.0);
		wall_found = 0;
		// ray_loop()
		while (!wall_found && ray.prev_dist < RENDER_DIST)
		{
			if (ray.dist[0] < ray.dist[1])
			{
				ray.map_check[0] += ray.step[0];
				ray.prev_dist = ray.dist[0];
				ray.dist[0] += ray.step_dist[0];
			}
			else
			{
				ray.map_check[1] += ray.step[1];
				ray.prev_dist = ray.dist[1];
				ray.dist[1] += ray.step_dist[1];
			}

			if ((ray.map_check[0] >= 0 && ray.map_check[0] < cub->map.w) &&
					(ray.map_check[1] >= 0 && ray.map_check[1] < cub->map.h))
			{
				if (cub->map.tiles[ray.map_check[1]][ray.map_check[0]])
					wall_found = 1;
			}
		}
		if (wall_found)
		{
			int tmp[2];
			tmp[0] = 50.0 * (p->x + ray.prev_dist * ray.norm[0]) - 3;
			tmp[1] = 50.0 * (p->y - ray.prev_dist * ray.norm[1]) - 3;
 			draw_square(cub, tmp, 6, 0x00ff00ff);
		}
	}
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

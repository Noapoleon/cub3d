/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +
 *                                                    :+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:17:05 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/08 23:12:03 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_ray *r, t_player *p, double x)
{
	x = ((2.0 * x) / (double)W_WIDTH) - 1.0;
	//r->angle = angle; // remove
	r->norm[0] = cos(p->rot) + cos(p->rot - M_PI_2) * x; // do outside of here only once for dir vector and perp cam thing
	r->norm[1] = sin(p->rot) + sin(p->rot - M_PI_2) * x;
	//r->step_dist[0] = sqrt(1 + (r->norm[1] / r->norm[0]) *
	//		(r->norm[1] / r->norm[0]));
	//r->step_dist[1] = sqrt(1 + (r->norm[0] / r->norm[1]) *
	//		(r->norm[0] / r->norm[1]));
	r->step_dist[0] = fabs(1.0 / r->norm[0]);
	r->step_dist[1] = fabs(1.0 / r->norm[1]);
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
	r->end = 0.0;
	r->side = 0;
}

static void	cast_rays(t_cub *cub, t_player *p)
{
	double			tmp; // remove
	static t_ray	ray;
	int				wall_found;
	int				line_height;
	int				line_col;

	// refresh_ray() -> loop of different angle rays but same position

	for (int i = 0; i < W_WIDTH; ++i)
	{
		init_ray(&ray, p, W_WIDTH - i);
		//init_ray(&ray, p, p->rot + (((M_PI / 180.0) * FOV) / (double)W_WIDTH) * (double)i - (M_PI / 180.0) * (FOV / 2.0));
		wall_found = 0;
		// ray_loop()
		while (!wall_found && ray.end <= RENDER_DIST)
		{
			if (ray.dist[0] < ray.dist[1])
			{
				ray.map_check[0] += ray.step[0];
				ray.end = ray.dist[0];
				ray.dist[0] += ray.step_dist[0];
				ray.side = 0;
			}
			else
			{
				ray.map_check[1] += ray.step[1];
				ray.end = ray.dist[1];
				ray.dist[1] += ray.step_dist[1];
				ray.side = 1;
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
			(void)tmp;
			if (ray.side == 0)
			{
				//tmp = ray.dist[0] - ray.step_dist[0];
				line_col = 0x00bb0000;
			}
			else
			{
				//tmp = ray.dist[1] - ray.step_dist[1];
				line_col = 0x000000bb;
			}

			//tmp = fabs(p->rot - ray.angle);
			//printf("tmp angle diff -> %lf\n", tmp);
			//tmp = ray.end * cos(tmp);
			//line_height = (int)((double)W_HEIGHT / (ray.end * cos(tmp))); // fish eye fix
			line_height = (int)((double)W_HEIGHT / ray.end);
			//line_height = (int)((double)W_HEIGHT / tmp);
			//line_height = (int)((double)W_HEIGHT * (1 / ray.end));
			if (line_height > W_HEIGHT)
				line_height = W_HEIGHT;
			//draw_vert_line(&cub->mlx, (int[2]){W_WIDTH - i, (W_HEIGHT - line_height) / 2}, line_height, line_col);
			draw_vert_line(&cub->mlx, (int[2]){W_WIDTH - i, -line_height / 2 + W_HEIGHT / 2}, line_height, line_col);
		}
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
	mlx_put_image_to_window(mlx->ptr, mlx->win, cub->props.no.img.ptr, 0, 0);
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

// Prints vertical line
void	draw_vert_line(t_mlx *mlx, int pos[2], int height, int col) // change for texture later
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (i >= 0 && i < W_HEIGHT)
			my_pixel_put(mlx, pos, col);
		pos[1]++;
		++i;
	}
}

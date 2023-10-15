/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:35:33 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/16 00:42:56 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	init_ray(t_ray *r, t_player *p, double cam_x)
{
	cam_x = ((2.0 * cam_x) / (double)W_WIDTH) - 1.0;
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
	r->side = 0;
}

static void	cast_rays(t_cub *cub, t_player *p)
{
	static t_ray	ray;
	int				wall_found;
	int				line_height;
	int				line_col;

	// refresh_ray() -> loop of different angle rays but same position

	for (int i = 0; i < W_WIDTH; ++i)
	{
		init_ray(&ray, p, i);
		wall_found = 0;
		// ray_loop()
		while (!wall_found && ray.last_dist <= RENDER_DIST)
		{
			if (ray.dist.x < ray.dist.y)
			{
				ray.map_check.x += ray.step.x;
				ray.last_dist = ray.dist.x;
				ray.dist.x += ray.step_dist.x;
				ray.side = 0;
			}
			else
			{
				ray.map_check.y += ray.step.y;
				ray.last_dist = ray.dist.y;
				ray.dist.y += ray.step_dist.y;
				ray.side = 1;
			}

			if ((ray.map_check.x >= 0 && ray.map_check.x < cub->map.w) &&
					(ray.map_check.y >= 0 && ray.map_check.y < cub->map.h))
			{
				if (cub->map.tiles[ray.map_check.y][ray.map_check.x])
					wall_found = 1;
			}
		}
		if (wall_found)
		{
			if (ray.side == 0)
				line_col = 0x00bb0000;
			else
				line_col = 0x000000bb;

			line_height = (int)(((double)W_HEIGHT) / ray.last_dist);
			if (line_height > W_HEIGHT)
				line_height = W_HEIGHT;
			draw_vert_line(&cub->mlx, (int[2]){i, -line_height / 2 + W_HEIGHT / 2}, line_height, line_col);
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

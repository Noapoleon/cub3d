/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:32:27 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/18 23:35:19 by nlegrand         ###   ########.fr       */
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

static int	get_tex_col(t_texture *t, int pos[2])
{
	char	*dst;

	if (pos[0] >= 0 && pos[0] < t->w
			&& pos[1] >= 0 && pos[1] < t->h)
	{
		dst = t->img.addr + (pos[1] * t->img.ll + pos[0] * (t->img.bpp / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

static double	get_wall_x(t_ray *r, t_player *p)
{
	double wall_x;

	if (r->side < 2)
	{
		wall_x = p->pos.x + (r->dir.x * r->last_dist);
		wall_x -= (int)wall_x;
	}
	else
	{
		wall_x = p->pos.y - (r->dir.y * r->last_dist);
		wall_x -= (int)wall_x;
	}
	if (r->side == 1 || r->side == 2)
		return (1.0 - wall_x);
	return (wall_x);
}

// Prints vertical line with texture
static void	draw_vert_line(t_mlx *mlx, t_props *props, t_ray *r, t_player *p)
{
	int		height;
	int		pos[2];
	int		tx_range[2];
	double	tx_step[2];
	int		tx_pos[2];
	//int	col;

	height = (int)((double)W_HEIGHT / r->last_dist);
	tx_range[0] = (W_HEIGHT - height) / 2;
	tx_range[1] = W_HEIGHT - tx_range[0]; //what? yes
	tx_step[0] = (double)props->walls[r->side].h / (double)height; // rename
	if (tx_range[0] >= 0)
		tx_step[1] =  0;
	else
		tx_step[1]  = ((height - W_HEIGHT) / 2) * tx_step[0];
	tx_pos[0] = (get_wall_x(r, p) * (double)props->walls[r->side].w);

	if (r->index == 940)
	{
		//printf("tx_range -> %d;%d\n", tx_range[0], tx_range[1]);
		printf("thing -> %lf\n", tx_step[1]);
		printf("thing2 -> %lf\n", (double)W_HEIGHT / (double)height);
	}

	if (r->index == 940)
		printf("tx_step -> %lf ; %lf\n", tx_step[0], tx_step[1]);

	pos[0] = r->index;
	pos[1] = 0;
	while (pos[1] < W_HEIGHT)
	{
		if (pos[1] < tx_range[0])
			my_pixel_put(mlx, pos, props->col_c);
		else if (pos[1] >= tx_range[1])
			my_pixel_put(mlx, pos, props->col_f);
		else
		{
			//my_pixel_put(mlx, pos, 0x00ff0000);

			tx_pos[1] = tx_step[1];
			my_pixel_put(mlx, pos, get_tex_col(&props->walls[r->side], tx_pos));
			tx_step[1] += tx_step[0];
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
			draw_vert_line(&cub->mlx, &cub->props, &ray, p);
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
void	my_pixel_put(t_mlx *m, int pos[2], int col)
{
	char	*dst;

	if (pos[0] >= 0 && pos[0] < m->w
			&& pos[1] >= 0 && pos[1] < m->h)
	{
		dst = m->img.addr + (pos[1] * m->img.ll + pos[0] * (m->img.bpp / 8));
		*(unsigned int *)dst = col;
	}
}

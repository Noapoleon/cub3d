/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 02:41:19 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 05:16:50 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Compute movement angle from inputs and store in vector
void	get_mov_vec(double rot, t_inputs *inputs, t_vec2df *mov)
{
	if (inputs->w - inputs->s && inputs->a - inputs->d)
	{
		if (inputs->w && inputs->a)
			rot += M_PI_4;
		else if (inputs->w)
			rot -= M_PI_4;
		else if (inputs->s && inputs->a)
			rot += 3.0 * M_PI_4;
		else if (inputs->s)
			rot -= 3.0 * M_PI_4;
	}
	else if (inputs->w - inputs->s && inputs->s)
		rot -= M_PI;
	else if (inputs->a - inputs->d && inputs->a)
		rot += M_PI_2;
	else if (inputs->a - inputs->d && inputs->d)
		rot -= M_PI_2;
	set_vec2df(mov, cos(rot), sin(rot));
}

// Boolean solid tile function
static int	is_solid_tile(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->w)
		return (0);
	if (y < 0 || y >= map->h)
		return (0);
	return (map->tiles[y][x] >= T_WALL && map->tiles[y][x] <= T_DOOR_C);
}

// Clamp player position if it gets withing 0.1 of a wall
void	clamp_pos(t_map *map, t_vec2df *pos)
{
	if (is_solid_tile(map, pos->x - 1, pos->y)
		&& (pos->x - (int)pos->x) <= 0.1)
		pos->x = (int)pos->x + 0.1;
	else if (is_solid_tile(map, pos->x + 1, pos->y)
		&& (pos->x - (int)pos->x) >= 0.9)
		pos->x = (int)pos->x + 0.9;
	if (is_solid_tile(map, pos->x, pos->y - 1)
		&& (pos->y - (int)pos->y) <= 0.1)
		pos->y = (int)pos->y + 0.1;
	else if (is_solid_tile(map, pos->x, pos->y + 1)
		&& (pos->y - (int)pos->y) >= 0.9)
		pos->y = (int)pos->y + 0.9;
}

// Modified version of init_ray so that it works the movement direction vector
// instead of camera vectors
void	init_ray_collision(t_ray *r, t_player *p, t_vec2df *mov, double r_dist)
{
	r->index = 0;
	set_vec2df(&r->dir, mov->x, mov->y);
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
	r->render_dist = r_dist;
}

// If necessary this function will be used to detect where the players location
// should be after moving
void	ray_collision(t_cub *cub, t_vec2df *new_pos, t_vec2df *mov)
{
	t_ray		r;
	double		render_dist;
	t_player	*p;

	p = &cub->player;
	render_dist = sqrt((new_pos->x - p->pos.x) * (new_pos->x - p->pos.x)
			+ (new_pos->y - p->pos.y) * (new_pos->y - p->pos.y));
	init_ray_collision(&r, p, mov, render_dist);
	ray_dda_loop(&r, cub);
	if (r.tile_type >= T_WALL && r.tile_type <= T_DOOR_C)
	{
		set_vec2df(new_pos, p->pos.x + r.dir.x * r.last_dist,
			p->pos.y - r.dir.y * r.last_dist);
		if (r.side == 1)
			new_pos->y -= 0.01;
		else if (r.side == 3)
			new_pos->x -= 0.01;
	}
}

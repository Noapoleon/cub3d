/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:29:12 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/20 21:05:21 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// calculates player rotation from mouse movement and/or keypress
static void	set_player_rotation(t_player *p, t_cub *cub)
{
	int		pos[2];
	double	prev_rot;

	prev_rot = p->rot;
	mlx_mouse_get_pos(cub->mlx.ptr, cub->mlx.win, &pos[0], &pos[1]);
	if (pos[0] != cub->mlx.w_mid)
	{
		p->rot += ((double)(cub->mlx.w_mid - pos[0]) * 0.001)
			* M_PI * MOUSE_SPEED;
		mlx_mouse_move(cub->mlx.ptr, cub->mlx.win, cub->mlx.w_mid,
				cub->mlx.h_mid);
	}
	if (cub->inputs.la - cub->inputs.ra)
		p->rot += ((double)cub->delta * 0.000001) *
			(cub->inputs.la - cub->inputs.ra) * M_PI * MOUSE_SPEED;
	if (prev_rot != p->rot)
	{
		p->rot = get_principal_angle(p->rot);
		set_vec2df(&p->dir, cos(p->rot), sin(p->rot));
		set_vec2df(&p->cam, cos(p->rot - M_PI_2) * p->ratio_fix,
				sin(p->rot - M_PI_2) * p->ratio_fix);
	}
}

// compute movement angle from inputs
static double get_mov_angle(double rot, t_inputs *inputs)
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
	else if (inputs->w - inputs->s)
	{
		if (inputs->s)
			rot -= M_PI;
	}
	else if (inputs->a - inputs->d)
	{
		if (inputs->a)
			rot += M_PI_2;
		else
			rot -= M_PI_2;
	}
	//else if
	//	(
	//else if (!inputs->w && inputs->s)
	//	rot += M_PI;
	//else if (inputs->a && !inputs->d)
	//	rot += M_PI_2;
	//else if (!inputs->a && inputs->d)
	//	rot -= M_PI_2;
	return (rot);
}

//static int	check_collision(t_map *map, t_vec2df *pos)
//{
//	int	tile_type;
//
//	tile_type = map->tiles[(int)pos->y][(int)pos->x];
//	if (tile_type != T_AIR && tile_type != T_DOOR_O)
//		return (1);
//	return (0);
//}

//void	clamp_pos(t_map *map, t_vec2df *pos)
//{
//	int	tile_type;
//
//	tile_type = map->tiles[(int)pos->y][(int)pos->x - 1];
//	if (tile_type >= T_WALL && tile_type <= T_DOOR_C
//			&& (pos->x - (int)pos->x) <= 0.1)
//		pos->x = (int)pos->x + 0.1;
//	tile_type = map->tiles[(int)pos->y][(int)pos->x + 1];
//	if (tile_type >= T_WALL && tile_type <= T_DOOR_C
//			&& (pos->x - (int)pos->x) >= 0.9)
//		pos->x = (int)pos->x + 0.9;
//	tile_type = map->tiles[(int)pos->y - 1][(int)pos->x];
//	if (tile_type >= T_WALL && tile_type <= T_DOOR_C
//			&& (pos->y - (int)pos->y) <= 0.1)
//		pos->y = (int)pos->y + 0.1;
//	tile_type = map->tiles[(int)pos->y + 1][(int)pos->x];
//	if (tile_type >= T_WALL && tile_type <= T_DOOR_C
//			&& (pos->y - (int)pos->y) >= 0.9)
//		pos->y = (int)pos->y + 0.9;
//}
static int	is_solid_tile(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->w)
		return (0);
	if (y < 0 || y >= map->h)
		return (0);
	return (map->tiles[y][x] >= T_WALL && map->tiles[y][x] <= T_DOOR_C);
}

static void	clamp_pos(t_map *map, t_vec2df *pos)
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

void	init_ray_collision(t_ray *r, t_player *p, double angle, double r_dist)
{
	r->index = 0;
	set_vec2df(&r->dir, cos(angle), sin(angle));
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

// move player using input keys and delta time
static void	set_player_location(t_player *p, t_cub *cub)
{
	double		mov_angle;
	t_vec2df	mov;
	t_vec2df	new_pos;
	double		delta_sec;
	t_ray		r;

	if (cub->inputs.w - cub->inputs.s || cub->inputs.a - cub->inputs.d)
	{
		mov_angle = get_mov_angle(p->rot, &cub->inputs);
		set_vec2df(&mov, cos(mov_angle), sin(mov_angle));
		delta_sec = (double)cub->delta * 0.000001;
		set_vec2df(&new_pos, p->pos.x + (delta_sec * PLAYER_SPEED * mov.x),
			p->pos.y - (delta_sec * PLAYER_SPEED * mov.y));
		if ((int)p->pos.x != (int)new_pos.x || (int)p->pos.y != (int)new_pos.y)
		{
			init_ray_collision(&r, p, mov_angle, sqrt((new_pos.x - p->pos.x) * (new_pos.x - p->pos.x) + (new_pos.y - p->pos.y) * (new_pos.y - p->pos.y)));
			ray_dda_loop(&r, cub);

			if (r.tile_type >= T_WALL && r.tile_type <= T_DOOR_C)
			{
				set_vec2df(&new_pos, p->pos.x + r.dir.x * r.last_dist,
						p->pos.y - r.dir.y * r.last_dist);
				if (r.side == 1)
					new_pos.y -= 0.001;
				else if (r.side == 3)
					new_pos.x -= 0.001;
			}
		}
		clamp_pos(&cub->map, &new_pos);
		set_vec2df(&p->pos, new_pos.x, new_pos.y);
	}
}

static void	handle_doors(t_inputs *i, t_player *p)
{
	static int	last_e;

	if (i->e && last_e == 0)
	{
		if (p->cursor && *(p->cursor) == T_DOOR_C)
			*(p->cursor) = T_DOOR_O;
		else if (p->cursor && *(p->cursor) == T_DOOR_O)
			*(p->cursor) = T_DOOR_C;
		last_e = 1;
	}
	else if (!i->e && last_e == 1)
		last_e = 0;
}

// move and rotate player
void	handle_inputs(t_cub *cub)
{

	set_player_rotation(&cub->player, cub);
	set_player_location(&cub->player, cub);
	handle_doors(&cub->inputs, &cub->player);
}

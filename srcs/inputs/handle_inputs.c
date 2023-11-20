/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:29:12 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/20 17:00:53 by nlegrand         ###   ########.fr       */
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

static int	check_collision(t_map *map, t_vec2df *pos)
{
	int	tile_type;

	tile_type = map->tiles[(int)pos->y][(int)pos->x];
	if (tile_type != T_AIR && tile_type != T_DOOR_O)
		return (1);
	return (0);
}

// move player using input keys and delta time
static void	set_player_location(t_player *p, t_cub *cub)
{
	double		mov_angle;
	double		delta_sec;
	t_vec2df	pos;

	if (cub->inputs.w - cub->inputs.s || cub->inputs.a - cub->inputs.d)
	{
		mov_angle = get_mov_angle(p->rot, &cub->inputs);
		delta_sec = (double)cub->delta * 0.000001;
		//init_ray_collision(&ray, p, mov_angle);
		//ray_dda_loop(&ray, cub);
		pos.x = p->pos.x + (delta_sec * PLAYER_SPEED
			* cos(mov_angle));
		pos.y = p->pos.y - (delta_sec * PLAYER_SPEED
			* sin(mov_angle));
		//if (ray.last_dist < sqrt(pow(pos.x - p->pos.x, 2.0) + pow(pos.y - p->pos.y, 2.0)))
		//	set_vec2df(&p->pos, p->pos.x + ray.dir.x * (ray.last_dist - 0.1), p->pos.y + ray.dir.y * (ray.last_dist - 0.1)); // change
		//else
		//	set_vec2df(&p->pos, pos.x, pos.y);
		if (check_collision(&cub->map, &pos))
		{
			printf("les murs c du poison, t nul\n");
			free_cub(cub);
			exit(EXIT_SUCCESS);
		}
		set_vec2df(&p->pos, pos.x, pos.y);
			//set_vec2df(&p->pos, pos.x, pos.y);
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

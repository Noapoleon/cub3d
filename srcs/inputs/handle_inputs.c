/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:29:12 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 05:17:07 by nlegrand         ###   ########.fr       */
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
		p->rot += ((double)cub->delta * 0.000001)
			* (cub->inputs.la - cub->inputs.ra) * M_PI * MOUSE_SPEED;
	if (prev_rot != p->rot)
	{
		p->rot = get_principal_angle(p->rot);
		set_vec2df(&p->dir, cos(p->rot), sin(p->rot));
		set_vec2df(&p->cam, cos(p->rot - M_PI_2) * p->ratio_fix,
			sin(p->rot - M_PI_2) * p->ratio_fix);
	}
}

// Move player using input keys and delta time
// Check for collision and handle it accordingly
static void	set_player_location(t_player *p, t_cub *cub)
{
	t_vec2df	mov;
	t_vec2df	new_pos;
	double		delta_sec;

	if (cub->inputs.w - cub->inputs.s || cub->inputs.a - cub->inputs.d)
	{
		get_mov_vec(p->rot, &cub->inputs, &mov);
		delta_sec = (double)cub->delta * 0.000001;
		set_vec2df(&new_pos, p->pos.x + (delta_sec * PLAYER_SPEED * mov.x),
			p->pos.y - (delta_sec * PLAYER_SPEED * mov.y));
		if ((int)p->pos.x != (int)new_pos.x || (int)p->pos.y != (int)new_pos.y)
			ray_collision(cub, &new_pos, &mov);
		clamp_pos(&cub->map, &new_pos);
		set_vec2df(&p->pos, new_pos.x, new_pos.y);
	}
}

// 
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

static void	handle_minimap(t_inputs *i, t_cub *cub)
{
	static int	last_m;

	if (i->m && last_m == 0)
	{
		cub->minimap = !cub->minimap;
		last_m = 1;
	}
	else if (!i->m && last_m == 1)
		last_m = 0;
}

// move and rotate player
void	handle_inputs(t_cub *cub)
{
	set_player_rotation(&cub->player, cub);
	set_player_location(&cub->player, cub);
	handle_doors(&cub->inputs, &cub->player);
	handle_minimap(&cub->inputs, cub);
}

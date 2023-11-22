/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:29:12 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/22 15:16:35 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// calculates player rotation from mouse movement and/or keypress
static void	set_player_rotation(t_player *p, t_cub *cub)
{
	double	prev_rot;

	prev_rot = p->rot;
	if (cub->inputs.la - cub->inputs.ra)
		p->rot += DELTA_SEC * (cub->inputs.la - cub->inputs.ra)
			* M_PI * MOUSE_SPEED;
	if (prev_rot != p->rot)
	{
		p->rot = get_principal_angle(p->rot);
		set_vec2df(&p->dir, cos(p->rot), sin(p->rot));
		set_vec2df(&p->cam, cos(p->rot - M_PI_2) * p->ratio_fix,
			sin(p->rot - M_PI_2) * p->ratio_fix);
	}
}

// Compute movement angle from inputs and store in vector
static void	get_mov_vec(double rot, t_inputs *inputs, t_vec2df *mov)
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

// Move player using input keys and delta time
// Check for collision and handle it accordingly
static void	set_player_location(t_player *p, t_cub *cub)
{
	t_vec2df	mov;

	if (cub->inputs.w - cub->inputs.s || cub->inputs.a - cub->inputs.d)
	{
		get_mov_vec(p->rot, &cub->inputs, &mov);
		set_vec2df(&p->pos, p->pos.x + (DELTA_SEC * PLAYER_SPEED * mov.x),
			p->pos.y - (DELTA_SEC * PLAYER_SPEED * mov.y));
	}
}

// move and rotate player
void	handle_inputs(t_cub *cub)
{
	set_player_rotation(&cub->player, cub);
	set_player_location(&cub->player, cub);
}

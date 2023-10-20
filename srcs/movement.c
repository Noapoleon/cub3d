/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:29:12 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/20 13:35:20 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static void	set_player_rotation(t_player *p, t_cub *cub)
{
	int		pos[2];

	mlx_mouse_get_pos(cub->mlx.ptr, cub->mlx.win, &pos[0], &pos[1]);
	if (pos[0] != cub->mlx.w_mid)
	{
		p->rot += ((double)(cub->mlx.w_mid - pos[0]) / 1000.0) * M_PI;
		//p->rot += ((double)cub->dt / 1000000.0)  *
		//	(((double)(cub->mlx.w_mid - pos[0]) / 10.0) * M_PI) * MOUSE_SPEED;
		p->rot = get_principal_angle(p->rot);
	}
	set_vec2df(&p->dir, cos(p->rot), sin(p->rot));
	set_vec2df(&p->cam, cos(p->rot - M_PI_2), sin(p->rot - M_PI_2));
}

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
	else if (!inputs->w && inputs->s)
		rot += M_PI;
	else if (inputs->a && !inputs->d)
		rot += M_PI_2;
	else if (!inputs->a && inputs->d)
		rot -= M_PI_2;
	return (rot);
}

static void	set_player_location(t_player *player, t_cub *cub)
{
	double	mov_angle;

	if (cub->inputs.s - cub->inputs.w || cub->inputs.d - cub->inputs.a)
	{
		mov_angle = get_mov_angle(player->rot, &cub->inputs);
		player->pos.x += ((double)cub->dt / 1000000.0) * PLAYER_SPEED
			* cos(mov_angle);
		player->pos.y -= ((double)cub->dt / 1000000.0) * PLAYER_SPEED
			* sin(mov_angle);
	}
}

void	do_player_movement(t_cub *cub)
{
	set_player_rotation(&cub->player, cub);
	set_player_location(&cub->player, cub);
}

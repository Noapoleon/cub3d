/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:29:12 by nlegrand          #+#    #+#             */
/*   Updated: 2023/09/16 11:42:24 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_rotation(t_player *player, t_mlx *mlx)
{
	int		pos[2];

	mlx_mouse_get_pos(mlx->ptr, mlx->win, &pos[0], &pos[1]);
	if (pos[0] != mlx->w_mid)
	{
		player->rot += ((double)(pos[0] - mlx->w_mid) / MOUSE_SPEED) * M_PI;
		if (player->rot <= 2.0 * -M_PI || player->rot > 2.0 * M_PI)
			player->rot = fmod(player->rot, 2.0 * M_PI);
	}
}

static double get_mov_vec(double rot, t_inputs *inputs)
{
	if (inputs->w - inputs->s && inputs->a - inputs->d)
	{
		if (inputs->w && inputs->a)
			rot -= M_PI_4;
		else if (inputs->w)
			rot += M_PI_4;
		else if (inputs->s && inputs->a)
			rot -= 3.0 * M_PI_4;
		else if (inputs->s)
			rot += 3.0 * M_PI_4;
	}
	else if (!inputs->w && inputs->s)
		rot += M_PI;
	else if (inputs->a && !inputs->d)
		rot -= M_PI_2;
	else if (inputs->d)
		rot += M_PI_2;
	return (rot);
}

static void	set_player_location(t_player *player, t_inputs *inputs, t_cub *cub)
{
	double	mov_vec;

	if (inputs->s - inputs->w || inputs->d - inputs->a)
	{
		mov_vec = get_mov_vec(player->rot, inputs);
		player->x += ((double)cub->dt / 1000000) * PLAYER_SPEED * cos(mov_vec);
		player->y += ((double)cub->dt / 1000000) * PLAYER_SPEED * sin(mov_vec);
	}
}

void	set_player_movement(t_cub *cub)
{
	set_player_rotation(&cub->player, &cub->mlx);
	set_player_location(&cub->player, &cub->inputs, cub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:29:12 by nlegrand          #+#    #+#             */
/*   Updated: 2023/09/14 20:16:36 by nlegrand         ###   ########.fr       */
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

static void	set_player_location(t_player *player, t_inputs *inputs, t_cub *cub)
{
	const double	mov_v = inputs->s - inputs->w;
	const double	mov_h = inputs->d - inputs->a;

	if (mov_h)
		player->x += ((double)cub->dt / 1000000) * PLAYER_SPEED * mov_h;
	if (mov_v)
		player->y += ((double)cub->dt / 1000000) * PLAYER_SPEED * mov_v;
	// add movement according to rotation
}

void	set_player_movement(t_cub *cub)
{
	set_player_rotation(&cub->player, &cub->mlx);
	set_player_location(&cub->player, &cub->inputs, cub);
}

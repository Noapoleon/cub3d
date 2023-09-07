/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:10:09 by nlegrand          #+#    #+#             */
/*   Updated: 2023/09/07 17:35:31 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Clears all the pixels of the image buffer to the specified color
void	clear_imgbuf(t_cub *cub, int col)
{
	// move in subfolder for graphics things later
	// replace with function that clears with ceiling and floor colors
	int		x;
	int		y;

	y = 0;
	while (y < cub->mlx.h)
	{
		x = 0;
		while (x < cub->mlx.w)
		{
			my_pixel_put(&cub->mlx, (int[2]){x, y}, col);
			++x;
		}
		++y;
	}
}

// Get the deltatime between the last call of this function and now
// Used the game loop
void	get_deltatime(t_cub *cub)
{
	static long	last = -1;
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	if (last == -1)
		last = now;
	cub->dt = now - last;
	last = now;
}

void	set_player_rotation(t_mlx *mlx, t_player *player)
{
	int		pos[2];

	mlx_mouse_get_pos(mlx->ptr, mlx->win, &pos[0], &pos[1]);
	//printf("x -> %d && y -> %d\n", pos[0], pos[1]);
	if (pos[0] != mlx->w_mid && mlx->focused)
	{
		//printf("delta -> %d\n", (double)(pos[0] - mlx->w_mid) / MOUSE_SPEED);
		player->rot += ((double)(pos[0] - mlx->w_mid) / MOUSE_SPEED) * M_PI;
		if (player->rot <= 2.0 * -M_PI || player->rot > 2.0 * M_PI)
			player->rot = fmod(player->rot, 2.0 * M_PI); // modulo of m_pi * 2??? or m_pi
		//printf("rot -> %lf\n", player->rot);
	}
	if (mlx->focused)
		mlx_mouse_move(mlx->ptr, mlx->win, mlx->w_mid, mlx->h_mid); // at the end
}

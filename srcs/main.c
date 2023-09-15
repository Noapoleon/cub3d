/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/09/14 20:00:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Useless function
int	main(int ac, char **av)
{
	t_cub	cub;

	errno = 0;
	if (setup_cub(&cub, ac, av) != 0)
		return (1);
	mlx_loop(cub.mlx.ptr);
	free_cub(&cub);
	return (0);
}

// main game loop
int	game_loop(t_cub *cub)
{
	get_deltatime(cub);
	if (cub->mlx.focused)
	{
		set_player_movement(cub);
		mlx_mouse_move(cub->mlx.ptr, cub->mlx.win, cub->mlx.w_mid,
				cub->mlx.h_mid);
	}
	draw_frame(cub, &cub->mlx, &cub->player);
	return (0);
}

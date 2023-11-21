/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 16:40:21 by nlegrand         ###   ########.fr       */
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
		refresh_sprite(cub, &cub->props.wall_anim);
		handle_inputs(cub);
		draw_frame(cub, &cub->mlx, &cub->player);
		//if (is_solid_tile(&cub->map, cub->player.pos.x, cub->player.pos.y + 1))
		//		printf("tile is solid\n");
		//else
		//	printf("tile isn't solid\n");
	}
	return (0);
}

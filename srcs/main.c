/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/22 14:49:58 by nlegrand         ###   ########.fr       */
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
	if (cub->mlx.focused)
	{
		handle_inputs(cub);
		draw_frame(cub, &cub->mlx, &cub->player);
	}
	return (0);
}

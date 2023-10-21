/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/21 21:32:17 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Useless function
int	main(int ac, char **av)
{
	t_cub	cub;

	//printf("truc -> %.30lf\n", tan(M_PI/2));
	//printf("truc2 -> %.30lf\n", sin(M_PI/2));
	//printf("truc3 -> %.30lf\n", cos(M_PI/2));
	errno = 0;
	if (setup_cub(&cub, ac, av) != 0)
		return (1);
	//display_scene(&cub); // remove
	mlx_loop(cub.mlx.ptr);
	free_cub(&cub);
	return (0);
}

// main game loop
int	game_loop(t_cub *cub)
{
	get_deltatime(cub);
	//print_fps(cub); // remove
	//print_mouse_pos(&cub->mlx); // remove
	if (cub->mlx.focused)
	{
		do_player_movement(cub);
		draw_frame(cub, &cub->mlx, &cub->player);
	}
	return (0);
}

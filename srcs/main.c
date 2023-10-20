/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/20 12:54:15 by nlegrand         ###   ########.fr       */
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
	static long	elapsed;
	static int	frames;

	get_deltatime(cub);
	elapsed += cub->dt;
	++frames;
	if (elapsed >= 1000000)
	{
		printf("%d fps\n", frames);
		elapsed = 0;
		frames = 0;
	}
	if (cub->mlx.focused)
	{
		do_player_movement(cub);
		mlx_mouse_move(cub->mlx.ptr, cub->mlx.win, cub->mlx.w_mid,
				cub->mlx.h_mid);
	}
	draw_frame(cub, &cub->mlx, &cub->player);
	return (0);
}

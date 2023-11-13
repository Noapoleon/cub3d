/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/13 17:41:00 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_clock(t_cub *cub, t_sprite *s)
{
	int	i;
	char	name[] = "textures/clock_xpm/clock_0.xpm";

	// settings
	s->n = 8;
	s->frames = malloc(sizeof(t_texture) * s->n);
	if (s->frames == NULL)
		return (printf("failed to alloc frames\n"), -1);
	s->cur = &s->frames[0];
	s->uspf = 10000;
	// mlx
	i = 0;
	while (i < s->n)
	{
		name[25] = '1' + i;
		printf("name -> %s\n", name);
		s->frames[i].path = name;
		if (open_texture(&cub->mlx, &s->frames[i]) == -1)
			return (printf("failed to open clock textures\n"), -1);
		++i;
	}
	return (0);
}

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
	if (init_clock(&cub, &cub.clock) == -1) // remoe later
		return (printf("failed to init clock frames\n"));
	mlx_loop(cub.mlx.ptr);
	free_cub(&cub);

	// remove
	//int i = 0;
	//while (i < cub.clock.n)
	//{
	//	if (cub.clock.frames[i].img.ptr)
	//		mlx_destroy_image(cub.mlx.ptr, cub.clock.frames[i].img.ptr);
	//	++i;
	//}
	//free(cub.clock.frames);
	
	return (0);
}

// main game loop
int	game_loop(t_cub *cub)
{
	get_deltatime(cub);
	print_fps(cub); // remove
	//print_mouse_pos(&cub->mlx); // remove
	if (cub->mlx.focused)
	{
		do_player_movement(cub);
		draw_frame(cub, &cub->mlx, &cub->player);
	}
	return (0);
}

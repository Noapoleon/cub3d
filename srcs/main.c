/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/19 18:04:59 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//int	init_clock(t_cub *cub, t_sprite *s)
//{
//	int	i;
//	char	name[] = "textures/clock_xpm/clock_0.xpm";
//
//	// settings
//	s->n = 8;
//	s->frames = malloc(sizeof(t_texture) * s->n);
//	if (s->frames == NULL)
//		return (printf("failed to alloc frames\n"), -1);
//	s->cur = &s->frames[0];
//	s->uspf = 10000;
//	// mlx
//	i = 0;
//	while (i < s->n)
//	{
//		name[25] = '1' + i;
//		printf("name -> %s\n", name);
//		s->frames[i].path = name;
//		if (open_texture(&cub->mlx, &s->frames[i]) == -1)
//			return (printf("failed to open clock textures\n"), -1);
//		++i;
//	}
//	return (0);
//}

static void	copy_frame(t_texture *src, t_texture *dst, int index)
{
	int	pos[2];

	pos[0] = src.h * index;
	pos[1] = 0;

	while (pos[0] < 
}

//int	open_texture(t_mlx *mlx, t_texture *t)
// sprites will divide in squares 
int	open_sprite(t_cub *cub, t_sprite *s)
{
	int	i;

	if (open_texture(&cub->mlx, &s->tex) != 0)
		return (-1);
	if (s->tex.w % s->tex.h != 0) // test edge cases
		return (ft_perr(CUB_ERR CE_SPRITE_RES), -1);
	s->num_frames = s->tex.w / s->tex.h;
	s->frames = malloc(sizeof(t_texture) * s->num_frames);
	if (s->frames == NULL)
		return (ft_perr(CUB_ERR CE_SPRITE_ALLOC, strerror(errno)), -1);
	s->frame = &s->frames[0];
	s->index = 0;
	s->delay = 200000;
	i = 0;
	while (i < s->num_frames)
	{
		s->frames[i].path = NULL; // dont free but still detect them somehow?
		s->frames[i].w = s->tex.h;
		s->frames[i].h = s->tex.h;
		s->frames[i].img.ptr = mlx_new_image(&cub->mlx, s->tex.h, s->tex.h);
		if (s->frames[i].img.ptr == NULL)
			return (ft_perr(CUB_ERR CE_SPRITE_IMG), -1);
		s->frames[i].img.addr = mlx_get_data_addr(s->frames[i].img.ptr,
				&s->frames[i].img.bpp, &s->frames[i].img.ll,
				&s->frames[i].img.endian);
		copy_frame(&s->tex, &s->frames[i], i);
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
		handle_inputs(cub);
		draw_frame(cub, &cub->mlx, &cub->player);
	}
	return (0);
}

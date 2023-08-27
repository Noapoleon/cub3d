/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/26 20:14:00 by nlegrand         ###   ########.fr       */
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
int	loop_hook(t_cub *cub)
{
	if (cub->redraw)
	{
		clear_img(cub, 0);
		view_map(cub);
		mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->mlx.img.ptr,
				0, 0);
		cub->redraw = 0;
	}
	return (0);
}

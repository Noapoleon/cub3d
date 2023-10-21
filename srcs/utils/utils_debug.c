/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:06:57 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/21 19:13:16 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// prints fps every second to the terminal
void	print_fps(t_cub *cub)
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
}

void	print_mouse_pos(t_mlx *mlx)
{
	int	pos[2];

	mlx_mouse_get_pos(mlx->ptr, mlx->win, &pos[0], &pos[1]);
	printf("mouse pos -> x:%d;y:%d\n", pos[0], pos[1]);
}

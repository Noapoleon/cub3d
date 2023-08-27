/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:11:15 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/24 22:04:37 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Sets array of ints to given val
// Assumes arr is valid and allocated
void	set_int_arr(int *arr, int size, int val)
{
	int	i;

	i = 0;
	while (i < size)
		arr[i++] = val;
}

void	free_props(t_props *props)
{
	free(props->no);
	free(props->so);
	free(props->we);
	free(props->ea);
}

void	free_map(t_map *map)
{
	int	i;

	if (map->tiles == NULL || map->h == -1)
		return ;
	i = 0;
	while (i < map->h)
		free(map->tiles[i++]);
	free(map->tiles);
}

void	free_mlx(t_mlx *mlx)
{
	if (mlx->ptr)
	{
		if (mlx->img.ptr)
			mlx_destroy_image(mlx->ptr, mlx->img.ptr);
		if (mlx->win)
			mlx_destroy_window(mlx->ptr, mlx->win);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
}

void	free_cub(t_cub *cub)
{
	free_props(&cub->props);
	free_map(&cub->map);
	free_mlx(&cub->mlx);
}

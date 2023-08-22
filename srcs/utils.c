/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:11:15 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/22 01:54:47 by nlegrand         ###   ########.fr       */
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

void	free_cub(t_cub *cub)
{
	free_props(&cub->props);
	free_map(&cub->map);
}

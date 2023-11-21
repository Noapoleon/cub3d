/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:46:10 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 00:46:50 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns the tile value from lines
int	get_tile_val(char c)
{
	if (c == ' ')
		return (-1);
	else if (ft_isdigit(c))
		return (c - '0');
	else
		return (0);
}

// Returns -1 if block around air tile is not airtile or wall
int	check_airtile_surround(t_map *map, int x, int y)
{
	int	**tiles;

	tiles = map->tiles;
	if (x == 0 || x == map->w - 1 || y == 0 || y == map->h - 1)
		return (-1);
	if (tiles[y][x - 1] == -1 || tiles[y][x + 1] == -1)
		return (-1);
	if (tiles[y - 1][x] == -1 || tiles[y + 1][x] == -1)
		return (-1);
	return (0);
}

// Safely allocates map
void	alloc_map_size(t_map *map, int width, int height)
{
	int	i;

	if (width < 3 || height < 3)
		return ((void)ft_perr(CUB_ERR CE_MAP_SMALL));
	map->tiles = malloc(sizeof(*map->tiles) * height);
	if (map->tiles == NULL)
		return ((void)ft_perr(CUB_ERR CE_MAP_ALLOC, strerror(errno)));
	i = 0;
	while (i < height)
	{
		map->tiles[i] = malloc(sizeof(**map->tiles) * width);
		if (map->tiles[i] == NULL)
		{
			while (i--)
				free(map->tiles[i]);
			free(map->tiles);
			return ((void)ft_perr(CUB_ERR CE_MAP_ALLOC, strerror(errno)));
		}
		set_int_arr(map->tiles[i], width, -1);
		++i;
	}
	return ((map->w = width), (void)(map->h = height));
}

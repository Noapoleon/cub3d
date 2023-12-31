/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:52:56 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 00:45:14 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Safely allocates the map 2D array
static int	alloc_map(t_map *map, t_list *cur, int count, int *offset)
{
	int		min_width;
	int		max_width;
	int		height;
	char	*tmp;

	min_width = INT_MAX;
	max_width = -1;
	height = 0;
	while (cur)
	{
		++height;
		tmp = get_line_start(cur->data);
		if (tmp[0] != '\0')
		{
			if (!is_map_str(tmp))
				return (ft_perr(CUB_ERR CE_LINE, count, CE_MAP_CHAR), -1);
			map->h = height;
			min_width = ft_min(min_width, tmp - (char *)cur->data);
			tmp = get_line_end(cur->data);
			max_width = ft_max(max_width, tmp - (char *)cur->data);
		}
		cur = cur->next;
	}
	alloc_map_size(map, max_width - min_width, map->h);
	return ((*offset = min_width), (map->tiles == NULL) * -1);
}

// If player tile is found sets the properties of player struct and replaces it
// it in the map with an air tile
static int	set_player(t_player *p, int x, int y, char c)
{
	if (p->pos.x != -1.0)
		return (-1);
	set_vec2df(&p->pos, x + 0.5, y + 0.5);
	if (c == 'N')
		p->rot = M_PI_2;
	else if (c == 'S')
		p->rot = M_PI_2 * 3.0;
	else if (c == 'W')
		p->rot = M_PI;
	else
		p->rot = 0;
	set_vec2df(&p->dir, cos(p->rot), sin(p->rot));
	set_vec2df(&p->cam, cos(p->rot - M_PI_2) * p->ratio_fix,
		sin(p->rot - M_PI_2) * p->ratio_fix);
	return (0);
}

// Using linked list for map fills the array with correct tiles
static int	fill_map(t_cub *cub, t_list *cur, int count, int offset)
{
	int		x;
	int		y;
	char	c;
	int		len_cur;

	y = 0;
	while (y < cub->map.h)
	{
		++count;
		x = 0;
		len_cur = ft_strlen(cur->data);
		while (x < cub->map.w && x < len_cur)
		{
			c = ((char *)cur->data)[offset + x];
			cub->map.tiles[y][x] = get_tile_val(c);
			if (ft_isalpha(c) && set_player(&cub->player, x, y, c) != 0)
				return (ft_perr(CUB_ERR CE_LINE, count, CE_PLAYER_DUP), -1);
			++x;
		}
		cur = cur->next;
		++y;
	}
	if (cub->player.pos.x == -1.0)
		return (ft_perr(CUB_ERR CE_PLAYER_NONE), -1);
	return (0);
}

// Checks for errors in the map format
static int	check_map(t_map *map, int count)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->h)
	{
		++count;
		x = 0;
		while (x < map->w)
		{
			if ((map->tiles[y][x] == 0 || map->tiles[y][x] == 3)
					&& check_airtile_surround(map, x, y) != 0)
				return (ft_perr(CUB_ERR CE_LINE, count, CE_MAP_BAD), -1);
			++x;
		}
		++y;
	}
	return (0);
}

// Reads chained list of lines, allocates and fills the map, also checks for
// errors in the map
int	get_map(t_cub *cub, t_list *cur, int count)
{
	char	*tmp;
	int		offset;

	while (cur)
	{
		tmp = get_line_start(cur->data);
		if (tmp[0] != '\0')
			break ;
		cur = cur->next;
	}
	if (cur == NULL)
		return (ft_perr(CUB_ERR CE_MAP_NONE), -1);
	if (alloc_map(&cub->map, cur, count, &offset) != 0)
		return (-1);
	if (fill_map(cub, cur, count, offset) != 0)
		return (free_map(&cub->map), -1);
	if (check_map(&cub->map, count) != 0)
		return (free_map(&cub->map), -1);
	return (0);
}

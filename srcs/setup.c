/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:45:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/23 05:37:57 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes properties variables to default values
static void	init_vars_props(t_props *props)
{
	set_int_arr(props->col_f, 3, -1);
	set_int_arr(props->col_c, 3, -1);
	props->no = NULL;
	props->so = NULL;
	props->we = NULL;
	props->ea = NULL;
}

// Initializes map variables to default values
static void	init_vars_map(t_map *map)
{
	map->w = -1;
	map->h = -1;
	map->x_offset = -1;
	map->tiles = NULL;
}

// Initializes player variables to default values
static void	init_vars_player(t_player *player)
{
	player->x = -1.0f;
	player->y = -1.0f;
	player->rot = -1.0f;
}

// Put all vars to initial values
static void	init_vars(t_cub *cub)
{
	init_vars_props(&cub->props);
	init_vars_map(&cub->map);
	init_vars_player(&cub->player);
}

// Reads scene, allocates resources and sets up the player
int	setup_cub(t_cub *cub, int ac, char **av)
{
	if (ac != 2)
		return (ft_dprintf(STDERR_FILENO, "Usage: %s <scene.cub>\n", av[0]), -1);
	init_vars(cub);
	if (parse_scene(cub, av[1]) != 0)
		return (-1);
	display_scene(cub);
	return (0);
}

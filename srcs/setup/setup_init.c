/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:52:56 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/24 22:00:45 by nlegrand         ###   ########.fr       */
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

// Initializes mlx variables to default values
static void	init_vars_mlx(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
	mlx->img.ptr = NULL;
	mlx->img.addr = NULL;
	mlx->img.bpp = 0;
	mlx->img.ll = 0;
	mlx->img.endian = 0;
	mlx->w = -1;
	mlx->h = -1;
}

// Put all vars to initial values
void	init_vars(t_cub *cub)
{
	init_vars_props(&cub->props);
	init_vars_map(&cub->map);
	init_vars_player(&cub->player);
	init_vars_mlx(&cub->mlx);
	cub->redraw = 0;
}


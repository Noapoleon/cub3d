/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:52:56 by nlegrand          #+#    #+#             */
/*   Updated: 2023/09/07 14:00:56 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes properties variables to default values
void	init_vars_props(t_props *props)
{
	set_int_arr(props->col_f, 3, -1);
	set_int_arr(props->col_c, 3, -1);
	props->no = NULL;
	props->so = NULL;
	props->we = NULL;
	props->ea = NULL;
}

// Initializes map variables to default values
void	init_vars_map(t_map *map)
{
	map->w = -1;
	map->h = -1;
	map->x_offset = -1;
	map->tiles = NULL;
}

// Initializes player variables to default values
void	init_vars_player(t_player *player)
{
	player->x = -1.0f;
	player->y = -1.0f;
	player->rot = 0.0f; // set by map orientation
	//player->mov = 0.0f; // zero should be for w
}

// Initializes mlx variables to default values
void	init_vars_mlx(t_mlx *mlx)
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
	mlx->w_mid = -1;
	mlx->h_mid = -1;
	mlx->focused = 0; // maybe set to 1
}

// Initializes inputs variables to default values
void	init_vars_inputs(t_inputs *inputs)
{
	inputs->w = 0;
	inputs->s = 0;
	inputs->a = 0;
	inputs->d = 0;
}

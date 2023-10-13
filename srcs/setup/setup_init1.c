/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:52:56 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/13 14:53:43 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes properties variables to default values
void	init_vars_props(t_props *props)
{
	set_int_arr(props->col_f, 3, -1);
	set_int_arr(props->col_c, 3, -1);
	init_vars_texture(&props->no);
	init_vars_texture(&props->so);
	init_vars_texture(&props->we);
	init_vars_texture(&props->ea);
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
	init_vars_imgbuf(&mlx->img);
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

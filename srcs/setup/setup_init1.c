/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:52:56 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 05:13:24 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes properties variables to default values
void	init_vars_props(t_props *props)
{
	props->col_f = -1;
	props->col_c = -1;
	init_vars_texture(&props->walls[0]);
	init_vars_texture(&props->walls[1]);
	init_vars_texture(&props->walls[2]);
	init_vars_texture(&props->walls[3]);
	init_vars_texture(&props->door[0]);
	init_vars_texture(&props->door[1]);
	init_vars_sprite(&props->wall_anim);
}

// Initializes map variables to default values
void	init_vars_map(t_map *map)
{
	map->w = -1;
	map->h = -1;
	map->tiles = NULL;
	map->size[0] = 10;
	map->size[1] = 10;
}

// Initializes player variables to default values
void	init_vars_player(t_player *p)
{
	set_vec2df(&p->pos, -1.0f, -1.0f);
	p->rot = 0.0f;
	set_vec2df(&p->dir, -1.0f, -1.0f);
	set_vec2df(&p->cam, -1.0f, -1.0f);
	p->ratio_fix = ((double)W_WIDTH / (double)W_HEIGHT) / 2.0;
	p->cursor = NULL;
}

// Initializes mlx variables to default values
void	init_vars_mlx(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
	init_vars_imgmlx(&mlx->img);
	mlx->w = -1;
	mlx->h = -1;
	mlx->w_mid = -1;
	mlx->h_mid = -1;
	mlx->focused = 0;
}

// Initializes inputs variables to default values
void	init_vars_inputs(t_inputs *inputs)
{
	inputs->w = 0;
	inputs->s = 0;
	inputs->a = 0;
	inputs->d = 0;
	inputs->e = 0;
	inputs->m = 0;
	inputs->la = 0;
	inputs->ra = 0;
}

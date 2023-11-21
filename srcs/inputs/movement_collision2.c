/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_collision2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:56:46 by juduval           #+#    #+#             */
/*   Updated: 2023/11/21 20:25:54 by juduval          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ray_collision_loop(t_ray *r, t_cub *cub)
{
	int	*tile;

	if (r->index == cub->mlx.w_mid)
		cub->player.cursor = NULL;
	while (r->last_dist <= r->render_dist)
	{
		dda_increment(r);
		if (r->last_dist >= r->render_dist)
			break ;
		if ((r->map_check.x >= 0 && r->map_check.x < cub->map.w)
			&& (r->map_check.y >= 0 && r->map_check.y < cub->map.h))
		{
			tile = &cub->map.tiles[r->map_check.y][r->map_check.x];
			if (*tile >= T_WALL && *tile <= T_DOOR_C)
			{
				r->tile_type = *tile;
				if (r->index == cub->mlx.w_mid && r->last_dist <= PLAYER_REACH)
					cub->player.cursor = tile;
				return (1);
			}
		}
	}
	r->side = -1;
	r->tile_type = -1;
	return (0);
}

// If necessary this function will be used to detect where the players location
// should be after moving
void	ray_collision(t_cub *cub, t_vec2df *new_pos, t_vec2df *mov)
{
	t_ray		r;
	double		render_dist;
	t_player	*p;

	p = &cub->player;
	render_dist = sqrt((new_pos->x - p->pos.x) * (new_pos->x - p->pos.x)
			+ (new_pos->y - p->pos.y) * (new_pos->y - p->pos.y));
	init_ray_collision(&r, p, mov, render_dist);
	ray_collision_loop(&r, cub);
	if (r.tile_type >= T_WALL && r.tile_type <= T_DOOR_C)
	{
		set_vec2df(new_pos, p->pos.x + r.dir.x * r.last_dist,
			p->pos.y - r.dir.y * r.last_dist);
		if (r.side == 1)
			new_pos->y -= 0.01;
		else if (r.side == 3)
			new_pos->x -= 0.01;
	}
}

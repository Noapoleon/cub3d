/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:46:33 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 15:44:38 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// returns color of tile color or map
int	get_map_color(int tile_type)
{
	if (tile_type == T_AIR)
		return (0x00cccccc);
	else if (tile_type == T_WALL || tile_type == T_WALL_ANIM)
		return (0x00eeeeee);
	else if (tile_type == T_DOOR_C)
		return (0x00eecccc);
	else if (tile_type == T_DOOR_O)
		return (0x00cceecc);
	else
		return (0x0);
}

void	dda_increment(t_ray *r)
{
	if (r->dist.x < r->dist.y)
	{
		r->map_check.x += r->step.x;
		r->last_dist = r->dist.x;
		r->dist.x += r->step_dist.x;
		r->side = (r->step.x > 0) + 2;
	}
	else
	{
		r->map_check.y += r->step.y;
		r->last_dist = r->dist.y;
		r->dist.y += r->step_dist.y;
		r->side = r->step.y > 0;
	}
}

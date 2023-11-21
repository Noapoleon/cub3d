/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:20:05 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 17:21:05 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns X coord of ray hit on wall
static double	get_wall_x(t_ray *r, t_player *p)
{
	double	wall_x;

	if (r->side < 2)
	{
		wall_x = p->pos.x + (r->dir.x * r->last_dist);
		wall_x -= (int)wall_x;
	}
	else
	{
		wall_x = p->pos.y - (r->dir.y * r->last_dist);
		wall_x -= (int)wall_x;
	}
	if (r->side == 1 || r->side == 2)
		return (1.0 - wall_x);
	return (wall_x);
}

static t_texture	*get_wall_tex(t_cub *cub, t_ray *r)
{
	if (r->tile_type == T_WALL)
		return (&cub->props.walls[r->side]);
	else if (r->tile_type == T_WALL_ANIM)
		return (cub->props.wall_anim.frame);
	else if (r->tile_type == T_DOOR_C)
		return (&cub->props.door[0]);
	else
		return (&cub->props.door[1]);
}

static void	init_texline(t_texline *tl, t_cub *cub, t_ray *r)
{
	if (r->side == -1)
	{
		tl->range[0] = cub->mlx.h_mid;
		tl->range[1] = cub->mlx.h_mid;
		return ;
	}
	tl->tex = get_wall_tex(cub, r);
	tl->height = (int)((double)W_HEIGHT / r->last_dist);
	tl->h_mid = tl->height / 2;
	tl->range[0] = cub->mlx.h_mid - tl->h_mid;
	tl->range[1] = W_HEIGHT - tl->range[0];
	tl->step[0] = (double)tl->tex->h / (double)tl->height;
	if (tl->range[0] >= 0)
		tl->step[1] = 0;
	else
		tl->step[1] = (tl->h_mid - cub->mlx.h_mid) * tl->step[0];
	tl->pos[0] = (get_wall_x(r, &cub->player) * (double)tl->tex->w);
	if (tl->pos[0] >= tl->tex->w)
		tl->pos[0] = tl->tex->w - 1;
}

static int	tex_sample_wall(t_texline *tl)
{
	int		col;

	tl->pos[1] = tl->step[1];
	if (tl->pos[1] >= tl->tex->h)
		tl->pos[1] = tl->tex->h - 1;
	col = get_pixel(&tl->tex->img, tl->pos);
	return (col);
}

// Prints vertical line with texture
void	draw_vert_line(t_cub *cub, t_ray *r)
{
	static t_texline	tl;
	int					pos[2];

	int	col; //remove
	static int truc;

	init_texline(&tl, cub, r);
	pos[0] = r->index;
	pos[1] = 0;
	while (pos[1] < W_HEIGHT)
	{
		if (pos[1] < tl.range[0])
			set_pixel(&cub->mlx.img, pos, cub->props.col_c);
		else if (pos[1] >= tl.range[1])
			set_pixel(&cub->mlx.img, pos, cub->props.col_f);
		else
		{
			col = tex_sample_wall(&tl);
			if (col == 0x00ff00ff && truc++ == 0)
			{
				printf("t pas sense colore mdr\n");
				printf("pos colli -> %d;%d\n", r->map_check.x, r->map_check.y);
				printf("side -> %d\n", r->side);
			}
			set_pixel(&cub->mlx.img, pos, tex_sample_wall(&tl));
			tl.step[1] += tl.step[0];
		}
		++pos[1];
	}
}

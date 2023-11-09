/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vert_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:20:05 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/09 10:33:55 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns X coord of ray hit on wall
static double	get_wall_x(t_ray *r, t_player *p)
{
	double wall_x;

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

static void	init_texline(t_texline *tl, t_cub *cub, t_ray *r)
{
	if (r->side == -1)
	{
		tl->range[0] = cub->mlx.h_mid;
		tl->range[1] = cub->mlx.h_mid;
		return ;
	}
	tl->height = (int)((double)W_HEIGHT / r->last_dist);
	tl->h_mid = tl->height / 2;
	tl->range[0] = cub->mlx.h_mid - tl->h_mid;
	tl->range[1] = W_HEIGHT - tl->range[0];
	tl->step[0] = (double)cub->props.walls[r->side].h / (double)tl->height; // parentheses?
	if (tl->range[0] >= 0)
		tl->step[1] =  0;
	else
		tl->step[1]  = (tl->h_mid - cub->mlx.h_mid) * tl->step[0];
	tl->pos[0] = (get_wall_x(r, &cub->player) *
			(double)cub->props.walls[r->side].w);
	if (tl->pos[0] >= cub->props.walls[r->side].w)
		tl->pos[0] = cub->props.walls[r->side].w - 1;
	tl->fog = r->last_dist / RENDER_DIST;
	if (tl->fog > 1.0)
		tl->fog = 1.0;
}

//static int	tex_apply_fog(int col, int col_f, double fog)
//{
//	int		r;
//	int		g;
//	int		b;
//
//	r = ((col >> 16) & 0xff) - ((double)((((col >> 16) & 0xff) - ((col_f >> 16) & 0xff)) * fog));
//	g = ((col >> 8) & 0xff) - ((double)(((col >> 8) & 0xff) - ((col_f >> 8) & 0xff)) * fog);
//	b = (col & 0xff) - ((double)((col & 0xff) - (col_f & 0xff)) * fog);
//	return ((r << 16) | (g << 8) | b);
//}

static int	tex_sample_wall(t_texline *tl, t_cub *cub,  t_ray *r)
{
	int		col;

	tl->pos[1] = tl->step[1];
	if (tl->pos[1] >= cub->props.walls[r->side].h)
		tl->pos[1] = cub->props.walls[r->side].h - 1;
	col = get_tex_col(&cub->props.walls[r->side], tl->pos);
	return (col); // remove
	//return (tex_apply_fog(col, cub->props.col_f, tl->fog));
}

// Prints vertical line with texture
void	draw_vert_line(t_cub *cub, t_ray *r)
{
	static t_texline	tl;
	int					pos[2];

	init_texline(&tl, cub, r);
	pos[0] = r->index;
	pos[1] = 0;
	while (pos[1] < W_HEIGHT)
	{
		if (pos[1] < tl.range[0])
			my_pixel_put(&cub->mlx, pos, cub->props.col_c);
		else if (pos[1] >= tl.range[1])
			my_pixel_put(&cub->mlx, pos, cub->props.col_f);
		else
		{
			my_pixel_put(&cub->mlx, pos, tex_sample_wall(&tl, cub, r));
			tl.step[1] += tl.step[0];
		}
		++pos[1];
	}
}

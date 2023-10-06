/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 05:20:42 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/05 17:37:44 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_map(t_map *map)
{
	int x = 0;
	int y = 0;

	int	*row;

	if (map->w == -1 || map->h == -1)
		return ;
	while (y < map->h)
	{
		row = map->tiles[y];
		x = 0;
		while (x < map->w)
		{
			if (row[x] == T_NONE)
				printf(" ");
			else if (row[x] == T_AIR)
				printf("0");
			else
				printf("1");
			++x;
		}
		printf("\n");
		++y;
	}
}
void	display_scene(t_cub *cub)
{
	printf("### SCENE BEG ###\n");
	printf("\nProperties:\n");
	printf("NO -> %s\n", cub->props.no);
	printf("SO -> %s\n", cub->props.so);
	printf("WE -> %s\n", cub->props.we);
	printf("EA -> %s\n", cub->props.ea);
	printf("F -> %d,%d,%d\n", cub->props.col_f[0], cub->props.col_f[1], cub->props.col_f[2]);
	printf("C -> %d,%d,%d\n", cub->props.col_c[0], cub->props.col_c[1], cub->props.col_c[2]);
	printf("\nPlayer:\n");
	printf("x -> %f, y -> %f\n", cub->player.x, cub->player.y);
	printf("rot -> %f\n", cub->player.rot);
	printf("\n");
	printf("\nMap:\n");
	printf("w -> %d, h -> %d\n", cub->map.w, cub->map.h);
	printf("x_offset -> %d\n", cub->map.x_offset);
	write_map(&cub->map);
	printf("\n### SCENE END ###\n");
}

void	draw_square(t_cub *cub, int pos[2], int size, int col)
{
	int	i;
	int	j;

	if (size < 0)
		return ;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			my_pixel_put(&cub->mlx, (int[2]){pos[0] + i, pos[1] + j}, col);
			++i;
		}
		++j;
	}
}

void	display_map(t_cub *cub)
{
	t_map		*map;
	int			i;
	int			j;
	int			pos[2];
	const double size = 50;

	map = &cub->map;
	j = 0;
	while (j < map->h)
	{
		i = 0;
		while (i < map->w)
		{
			if (map->tiles[j][i] == 1)
			{
				//pos[0] = size * i + i;
				//pos[1] = size * j + j;
				pos[0] = size * i;
				pos[1] = size * j;
				draw_square(cub, pos, size, 0x00ff0000);
			}
			++i;
		}
		++j;
	}

	//printf("player: x -> %lf; y -> %lf\n", cub->player.x, cub->player.y);
	//float useless;

	pos[0] = (int)(cub->player.x * size);
	pos[1] = (int)(cub->player.y * size);
	//pos[0] = (int)cub->player.x * size + (int)(modff(cub->player.x, &useless) * (float)size);
	//pos[1] = (int)cub->player.y * size + (int)(modff(cub->player.y, &useless) * (float)size);
	//draw_square(cub, pos, 5, 0x0000ff00);
	display_rot(cub, pos);
}

void display_inputs(t_cub *cub, int pos[2])
{
	t_inputs *inputs = &cub->inputs;
	int	size = 60;

	if (inputs->w)
		draw_square(cub, (int[2]){pos[0] + size, pos[1]}, size, 0x00ff0000);
	if (inputs->s)
		draw_square(cub, (int[2]){pos[0] + size, pos[1] + size}, size, 0x00ff0000);
	if (inputs->a)
		draw_square(cub, (int[2]){pos[0], pos[1] + size}, size, 0x00ff0000);
	if (inputs->d)
		draw_square(cub, (int[2]){pos[0] + size * 2, pos[1] + size}, size, 0x00ff0000);
}

void	display_rot(t_cub *cub, int pos[2])
{
	double	size = 30.0;
	int		dot = 6;

	draw_square(cub, (int[2]){pos[0] - dot / 2, pos[1] - dot / 2}, dot, 0x0000ff00);
	pos[0] += cos(cub->player.rot) * size - dot / 2;
	pos[1] -= sin(cub->player.rot) * size + dot / 2;
	draw_square(cub, pos, dot, 0x000000ff);
}

//void	display_movdir(t_cub *cub, int pos[2])
//{
//	double size = 30.0;
//
//	double inputdir[2];
//	inputdir[0] = cub->inputs.w - cub->inputs.s;
//	inputdir[1] = cub->inputs.d - cub->inputs.a;
//
//	double movdir = atan(inputdir[0] / inputdir[1]);
//	//double movdir = atan(inputdir[1] / inputdir[0]);
//
//	draw_square(cub, pos, 5, 0x0000ff00);
//	pos[0] += cos(movdir) * size;
//	pos[1] += sin(movdir) * size;
//	draw_square(cub, pos, 5, 0x000000ff);
//}

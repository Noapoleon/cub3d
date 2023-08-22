/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 05:20:42 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/22 04:05:52 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_map(t_list *lst)
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		printf("%s\n", (char *)(cur->data));
		cur = cur->next;
	}
}


void	display_map(t_map *map)
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
	display_map(&cub->map);
	printf("\n### SCENE END ###\n");
}

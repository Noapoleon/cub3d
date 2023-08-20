/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 05:20:42 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/21 00:42:58 by nlegrand         ###   ########.fr       */
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

void	display_scene(t_cub *cub)
{
	printf("### SCENE BEG ###\n");
	printf("Properties:\n");
	printf("NO -> %s\n", cub->props.no);
	printf("SO -> %s\n", cub->props.so);
	printf("WE -> %s\n", cub->props.we);
	printf("EA -> %s\n", cub->props.ea);
	printf("\n");
	printf("Map:\n");
	printf("w -> %d, h -> %d\n", cub->map.w, cub->map.h);
	printf("map [ .... ] (use display_map)\n");
	printf("\n");
	printf("Player:\n");
	printf("x -> %f, y -> %f\n", cub->player.x, cub->player.y);
	printf("rot -> %f\n", cub->player.rot);
	printf("### SCENE END ###\n");
}

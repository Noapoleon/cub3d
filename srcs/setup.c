/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:45:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/14 04:59:19 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Put all vars to initial values
static void	init_vars(t_cub *cub)
{
	cub->map.blocks = NULL;
	set_int_arr(cub->map.col_flr, 3, -1);
	set_int_arr(cub->map.col_cil, 3, -1);
	cub->map.no = NULL;
	cub->map.so = NULL;
	cub->map.we = NULL;
	cub->map.ea = NULL;
	cub->player.x = 0.0;
	cub->player.y = 0.0;
	cub->player.rot = 0;
}

// Reads maps, allocates resources and sets up the player
int	setup_cub(t_cub *cub, int ac, char **av)
{
	if (ac != 2)
		return (ft_dprintf(STDERR_FILENO, "Usage: %s <map.cub>\n", av[0]), -1);
	init_vars(cub);
	if (parse_map(cub, av[1]) == -1)
		return (-1);
	return (0);
}

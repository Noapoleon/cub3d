/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:45:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/24 17:28:41 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Reads scene, allocates resources and sets up the player
int	setup_cub(t_cub *cub, int ac, char **av)
{
	// check W_WIDHT AND W_HEIGHT for bad values
	if (ac != 2)
		return (ft_dprintf(STDERR_FILENO, "Usage: %s <scene.cub>\n", av[0]), -1);
	init_vars(cub);
	if (parse_scene(cub, av[1]) != 0)
		return (-1);
	if (setup_mlx(cub, &cub->mlx) != 0)
		return (free_props(&cub->props), free_map(&cub->map), -1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:45:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/09/02 08:48:11 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Put all vars to initial values
static void	init_vars(t_cub *cub)
{
	init_vars_props(&cub->props);
	init_vars_map(&cub->map);
	init_vars_player(&cub->player);
	init_vars_mlx(&cub->mlx);
	init_vars_inputs(&cub->inputs);
}

// Reads scene, allocates resources and sets up the player
int	setup_cub(t_cub *cub, int ac, char **av)
{
	// check W_WIDHT AND W_HEIGHT for bad values
	if (ac != 2)
		return (ft_dprintf(STDERR_FILENO, "Usage: %s <scene.cub>\n", av[0]), -1);
	if (W_WIDTH < 100 || W_HEIGHT < 100) // test
		return (ft_perr(CUB_ERR CE_MLX_BADRES), -1);
	init_vars(cub);
	if (parse_scene(cub, av[1]) != 0)
		return (-1);
	if (setup_mlx(cub, &cub->mlx) != 0)
		return (free_props(&cub->props), free_map(&cub->map), -1);
	return (0);
}

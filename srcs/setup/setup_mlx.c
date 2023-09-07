/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:20:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/09/07 16:36:57 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//static void validate_pos(t_cub *cub, t_player *player, float new_pos[2])
//{
//	if (cub->map.tiles[(int)new_pos[1]][(int)new_pos[0]] == 0)
//	{
//		player->x = new_pos[0];
//		player->y = new_pos[1];
//	}
//}

// Uses mlx functions to open the mlx window
// Returns 0 on success, -1 otherwise
int	setup_mlx(t_cub *cub, t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		return (ft_perr(CUB_ERR CE_MLX_PTR), -1);
	mlx->win = mlx_new_window(mlx->ptr, W_WIDTH, W_HEIGHT, W_TITLE);
	if (mlx->win == NULL)
		return (ft_perr(CUB_ERR CE_MLX_WIN), free_mlx(mlx), -1);
	mlx->img.ptr = mlx_new_image(mlx->ptr, W_WIDTH, W_HEIGHT);
	if (mlx->img.ptr == NULL)
		return (ft_perr(CUB_ERR CE_MLX_IMG), free_mlx(mlx), -1);
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.ll,
			&mlx->img.endian);
	mlx->w = W_WIDTH;
	mlx->h = W_HEIGHT;
	mlx->w_mid = W_WIDTH / 2;
	mlx->h_mid = W_HEIGHT / 2;
	set_mlx_hooks(cub, mlx);
	return (0);
}

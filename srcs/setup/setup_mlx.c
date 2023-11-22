/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduval <juduval@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:20:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/22 14:47:33 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// open all property textures
// returns -1 on error, 0 otherwise
static int	open_props_textures(t_mlx *mlx, t_props *props)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (open_texture(mlx, &props->walls[i]) != 0)
			return (ft_perr(CUB_ERR CE_TEX_OPEN, props->walls[i].path), -1);
		++i;
	}
	return (0);
}

// Uses mlx functions to open the mlx window
// Returns 0 on success, -1 otherwise
int	setup_mlx(t_cub *cub, t_mlx *mlx, t_props *props)
{
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		return (ft_perr(CUB_ERR CE_MLX_PTR), -1);
	mlx->win = mlx_new_window(mlx->ptr, W_WIDTH, W_HEIGHT, W_TITLE);
	if (mlx->win == NULL)
		return (ft_perr(CUB_ERR CE_MLX_WIN), free_mlx(mlx, props), -1);
	mlx->img.ptr = mlx_new_image(mlx->ptr, W_WIDTH, W_HEIGHT);
	if (mlx->img.ptr == NULL)
		return (ft_perr(CUB_ERR CE_MLX_IMG), free_mlx(mlx, props), -1);
	set_imgmlx_data(&mlx->img, W_WIDTH, W_HEIGHT);
	if (open_props_textures(mlx, props) == -1)
		return (free_mlx(mlx, props), -1);
	mlx->w = W_WIDTH;
	mlx->h = W_HEIGHT;
	mlx->w_mid = W_WIDTH / 2;
	mlx->h_mid = W_HEIGHT / 2;
	set_mlx_hooks(cub, mlx);
	mlx_mouse_move(mlx->ptr, mlx->win, mlx->w_mid, mlx->h_mid);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:20:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/19 17:12:10 by nlegrand         ###   ########.fr       */
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
			return (ft_perr(CUB_ERR CE_TEXTURE_OPEN, props->walls[i].path), -1);
		if (i < 2 && open_texture(mlx, &props->door[i]) != 0)
			return (ft_perr(CUB_ERR CE_TEXTURE_OPEN, props->door[i].path), -1);
		++i;
	}
	//if (open_texture(mlx, &props->wall_a) == -1)
	//	return (ft_perr(CUB_ERR CE_TEXTURE_OPEN, props->wall_a.path), -1);
	return (0);
}

// Uses mlx functions to open the mlx window
// Returns 0 on success, -1 otherwise
int	setup_mlx(t_cub *cub, t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		return (ft_perr(CUB_ERR CE_MLX_PTR), -1);
	mlx->win = mlx_new_window(mlx->ptr, W_WIDTH, W_HEIGHT, W_TITLE);
	if (mlx->win == NULL)
		return (ft_perr(CUB_ERR CE_MLX_WIN), free_mlx(&cub->mlx, &cub->props), -1);
	mlx->img.ptr = mlx_new_image(mlx->ptr, W_WIDTH, W_HEIGHT);
	if (mlx->img.ptr == NULL)
		return (ft_perr(CUB_ERR CE_MLX_IMG), free_mlx(&cub->mlx, &cub->props), -1);
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.ll,
			&mlx->img.endian);
	if (open_props_textures(mlx, &cub->props) == -1)
		return (free_mlx(&cub->mlx, &cub->props), -1);
	mlx->w = W_WIDTH;
	mlx->h = W_HEIGHT;
	mlx->w_mid = W_WIDTH / 2;
	mlx->h_mid = W_HEIGHT / 2;
	set_mlx_hooks(cub, mlx);
	mlx_mouse_move(cub->mlx.ptr, cub->mlx.win, cub->mlx.w_mid, cub->mlx.h_mid);
	return (0);
}

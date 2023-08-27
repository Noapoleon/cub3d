/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:20:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/26 19:51:07 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_hook(int keycode, t_cub *cub)
{
	printf("keycode -> %d\n", keycode); // remove
	if (keycode == XK_w)
		cub->player.y -= 1.0f;
	if (keycode == XK_s)
		cub->player.y += 1.0f;
	if (keycode == XK_a)
		cub->player.x -= 1.0f;
	if (keycode == XK_d)
		cub->player.x += 1.0f;
	if (keycode == XK_Escape)
		mlx_loop_end(cub->mlx.ptr);
	cub->redraw = 1;
	return (0);
}

static int	set_hooks(t_cub *cub, t_mlx *mlx)
{
	mlx_key_hook(mlx->win, &key_hook, cub);
	mlx_loop_hook(mlx->ptr, &loop_hook, cub);
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
		return (ft_perr(CUB_ERR CE_MLX_WIN), free_mlx(mlx), -1);
	mlx->img.ptr = mlx_new_image(mlx->ptr, W_WIDTH, W_HEIGHT);
	if (mlx->img.ptr == NULL)
		return (ft_perr(CUB_ERR CE_MLX_IMG), free_mlx(mlx), -1);
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.ll,
			&mlx->img.endian);
	mlx->w = W_WIDTH;
	mlx->h = W_HEIGHT;
	set_hooks(cub, mlx);
	mlx_do_key_autorepeaton(mlx->ptr);
	return (0);
}

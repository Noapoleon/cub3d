/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:41:09 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/19 15:18:14 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Disables focus property of cub struct for input handling
static int	disable_focus_hook(t_cub *cub)
{
	cub->mlx.focused = 0;
	init_vars_inputs(&cub->inputs);
	//mlx_mouse_show(cub->mlx.ptr, cub->mlx.win);
	return (0);
}

// Enables focus property of cub struct for input handling
static int	enable_focus_hook(t_cub *cub)
{
	cub->mlx.focused = 1;
	//mlx_mouse_hide(cub->mlx.ptr, cub->mlx.win); // leaks
	return (0);
}

int	set_mlx_hooks(t_cub *cub, t_mlx *mlx)
{
	mlx_hook(mlx->win, DestroyNotify, SubstructureNotifyMask, &mlx_loop_end,
		mlx->ptr);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &keypress_hook, cub);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, &keyrelease_hook, cub);
	mlx_hook(mlx->win, FocusOut, FocusChangeMask, &disable_focus_hook, cub);
	mlx_hook(mlx->win, FocusIn, FocusChangeMask, &enable_focus_hook, cub);
	mlx_loop_hook(mlx->ptr, &game_loop, cub);
	return (0);
}

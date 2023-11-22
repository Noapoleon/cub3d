/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:41:09 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/22 16:12:53 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Disables focus property of cub struct for input handling
static int	disable_focus_hook(t_cub *cub)
{
	cub->mlx.focused = 0;
	init_vars_inputs(&cub->inputs);
	return (0);
}

// Enables focus property of cub struct for input handling
static int	enable_focus_hook(t_cub *cub)
{
	cub->mlx.focused = 1;
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

// Hooked to KeyPress event
int	keypress_hook(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->inputs.w = 1;
	if (keycode == XK_s)
		cub->inputs.s = 1;
	if (keycode == XK_a)
		cub->inputs.a = 1;
	if (keycode == XK_d)
		cub->inputs.d = 1;
	if (keycode == XK_e)
		cub->inputs.e = 1;
	if (keycode == XK_m)
		cub->inputs.m = 1;
	if (keycode == XK_Left)
		cub->inputs.la = 1;
	if (keycode == XK_Right)
		cub->inputs.ra = 1;
	if (keycode == XK_Escape)
		mlx_loop_end(cub->mlx.ptr);
	return (0);
}

// Hooked to KeyRelease event
int	keyrelease_hook(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->inputs.w = 0;
	if (keycode == XK_s)
		cub->inputs.s = 0;
	if (keycode == XK_a)
		cub->inputs.a = 0;
	if (keycode == XK_d)
		cub->inputs.d = 0;
	if (keycode == XK_e)
		cub->inputs.e = 0;
	if (keycode == XK_m)
		cub->inputs.m = 0;
	if (keycode == XK_Left)
		cub->inputs.la = 0;
	if (keycode == XK_Right)
		cub->inputs.ra = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:35:16 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/21 21:05:41 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (keycode == XK_Left)
		cub->inputs.la = 0;
	if (keycode == XK_Right)
		cub->inputs.ra = 0;
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:21:15 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 01:01:32 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_vec2df(t_vec2df *v, double x, double y)
{
	if (v)
	{
		v->x = x;
		v->y = y;
	}
}

void	set_vec2di(t_vec2di *v, int x, int y)
{
	if (v)
	{
		v->x = x;
		v->y = y;
	}
}

// Returns an angle in radians between 0 and 2 * M_PI
double	get_principal_angle(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0.0)
		angle += 2.0 * M_PI;
	return (angle);
}

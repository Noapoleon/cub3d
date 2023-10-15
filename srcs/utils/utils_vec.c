/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:21:15 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/15 22:23:58 by nlegrand         ###   ########.fr       */
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

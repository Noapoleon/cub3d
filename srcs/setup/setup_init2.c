/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:11:05 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/13 14:54:18 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes texture variables to default values
void	init_vars_texture(t_texture *t)
{
	t->path = NULL;
	init_vars_imgbuf(&t->img);
	t->w = -1;
	t->h = -1;
}


// Initializes imgbuf variables to default values
void	init_vars_imgbuf(t_imgbuf *img)
{
	img->ptr = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->ll = 0;
	img->endian = 0;
}

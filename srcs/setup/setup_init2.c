/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:11:05 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/19 22:10:03 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes texture variables to default values
void	init_vars_texture(t_texture *t)
{
	t->path = NULL;
	init_vars_imgmlx(&t->img);
	t->w = -1;
	t->h = -1;
}


// Initializes imgbuf variables to default values
void	init_vars_imgmlx(t_imgmlx *img)
{
	img->ptr = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->ll = 0;
	img->endian = 0;
	img->w = -1;
	img->h = -1;
}

void	init_vars_sprite(t_sprite *s)
{
	init_vars_texture(&s->tex);
	s->num_frames = 0;
	s->frames = NULL;
	s->index = -1;
	s->frame = NULL;
	s->delay = -1;
	s->elapsed = 0;
}


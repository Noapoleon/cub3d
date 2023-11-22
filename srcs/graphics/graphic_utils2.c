/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:49:26 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/22 14:34:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// stores image information in imgmlx struct properly in a concise function
void	set_imgmlx_data(t_imgmlx *img, int width, int height)
{
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->ll, &img->endian);
	img->w = width;
	img->h = height;
}

// Opens single texture file and fills in texture struct with info
int	open_texture(t_mlx *mlx, t_texture *t)
{
	if (t->path == NULL)
		return (-1);
	t->img.ptr = mlx_xpm_file_to_image(mlx->ptr, t->path, &t->w, &t->h);
	if (t->img.ptr == NULL)
		return (-1);
	set_imgmlx_data(&t->img, t->w, t->h);
	return (0);
}

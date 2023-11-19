/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:11:15 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/19 22:58:44 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_props(t_props *props)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (props->walls[i].path)
			free(props->walls[i].path);
		if (i < 2 && props->door[i].path)
			free(props->walls[i].path);
		++i;
	}
	if (props->wall_anim.tex.path)
		free(props->wall_anim.tex.path);
}

void	free_map(t_map *map)
{
	int	i;

	if (map->tiles == NULL || map->h == -1)
		return ;
	i = 0;
	while (i < map->h)
		free(map->tiles[i++]);
	free(map->tiles);
}

void	free_imgmlx(t_mlx *mlx, t_imgmlx *img)
{
	if (mlx->ptr && img->ptr)
		mlx_destroy_image(mlx->ptr, img->ptr);
}

void	free_mlx(t_mlx *mlx, t_props *props)
{
	int	i;

	if (mlx->ptr == NULL)
		return ;
	i = 0;
	while (i < 4)
	{
		free_imgmlx(mlx, &props->walls[i].img);
		if (i < 2)
			free_imgmlx(mlx, &props->door[i].img);
		++i;
	}
	free_imgmlx(mlx, &props->wall_anim.tex.img);
	i = 0;
	while (props->wall_anim.frames && i < props->wall_anim.num_frames)
		free_imgmlx(mlx, &props->wall_anim.frames[i++].img);
	free_imgmlx(mlx, &mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
}

void	free_cub(t_cub *cub)
{
	free_props(&cub->props);
	free_mlx(&cub->mlx, &cub->props);
	free_map(&cub->map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:10:09 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/15 22:31:08 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Sets array of ints to given val
// Assumes arr is valid and allocated
void	set_int_arr(int *arr, int size, int val)
{
	int	i;

	i = 0;
	while (i < size)
		arr[i++] = val;
}

// Clears all the pixels of the image buffer to the specified color
void	clear_imgbuf(t_cub *cub, int col)
{
	// move in subfolder for graphics things later
	// replace with function that clears with ceiling and floor colors
	int		x;
	int		y;

	y = 0;
	while (y < cub->mlx.h)
	{
		x = 0;
		while (x < cub->mlx.w)
		{
			my_pixel_put(&cub->mlx, (int[2]){x, y}, col);
			++x;
		}
		++y;
	}
}

// Get the deltatime between the last call of this function and now
// Used the game loop
void	get_deltatime(t_cub *cub)
{
	static long	last = -1;
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	if (last == -1)
		last = now;
	cub->dt = now - last;
	last = now;
}

// Returns an angle in radians between 0 and 2 * M_PI
double	get_principal_angle(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0.0)
		angle += 2.0 * M_PI;
	return (angle);
}

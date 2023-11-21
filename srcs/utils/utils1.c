/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:10:09 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 01:04:59 by nlegrand         ###   ########.fr       */
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

// Get the deltatime between the last call of this function and now
// Used the game loop
void	get_deltatime(t_cub *cub)
{
	static long		last = -1;
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	if (last == -1)
		last = now;
	cub->delta = now - last;
	last = now;
}

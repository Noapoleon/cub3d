/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:10:09 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/22 14:28:01 by nlegrand         ###   ########.fr       */
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

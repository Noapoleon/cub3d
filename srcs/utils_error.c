/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:25:00 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/01 17:54:48 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_err(char *err)
{
	ft_dprintf(STDERR_FILENO, CUB_ERR);
	ft_dprintf(STDERR_FILENO, err);
}

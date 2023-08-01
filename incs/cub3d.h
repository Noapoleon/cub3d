/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:43 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/01 18:52:43 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "mlx.h"

# define CUB_ERR			"\e[31;7;1m[CUB3D ERROR]\e[0m "
# define CE_SETUP			"Setup failed\n"
# define CE_MAP_PATH_NULL	"Map path is NULL\n"
# define CE_MAP_PATH_FORMAT	"Map path wrong format, \
file name must end with '.map'\n"
# define CE_MAP_DIRECTORY	"Map path is a directory\n"
# define CE_MAP_OPEN		"Failed to open map: %s\n"


typedef struct s_cub	t_cub;

struct s_cub
{

};

// ----- //
// SETUP //
// ----- //
int	setup_cub(t_cub *cub, int ac, char **av);

// ----- //
// UTILS //
// ----- //
void	print_err(char *err);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:43 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/14 05:21:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
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
# define CE_MAP_OPEN		"Failed to open map: %s: %s\n"
# define CE_MAP_READ		"Failed to read map: %s\n\n"
# define CE_MAP_LINE		"Map parsing error at line %d: %s\n"

typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_cub	t_cub;

struct s_map
{
	int		**blocks;
	int		col_flr[3];
	int		col_cil[3];
	// not sure how to store images yet, probably an mlx thing
	// but for now let's just store the path
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
};
struct s_player
{
	double	x;
	double	y;
	long	rot;
};
struct s_cub
{
	t_map		map;
	t_player	player;

};

// ----- //
// SETUP //
// ----- //
int		setup_cub(t_cub *cub, int ac, char **av);

// ------ //
// PARSER //
// ------ //
int		parse_map(t_cub *cub, const char *map_path);

// ----- //
// UTILS //
// ----- //
void	set_int_arr(int *arr, int size, int val);
// error
void	print_err(char *err);

// TEST CODE REMOVE LATER -------------------------------------------------------
void	show_map(t_list *lst);

#endif

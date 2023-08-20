/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:43 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/21 01:02:46 by nlegrand         ###   ########.fr       */
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

# define CUB_ERR				"Error\n"
# define CE_SCENE_PATH_NULL		"Scene path is NULL\n"
# define CE_SCENE_PATH_FORMAT	"Scene path wrong format, \
file name must end with '.map'\n"
# define CE_SCENE_DIRECTORY		"Scene path is a directory\n"
# define CE_SCENE_OPEN			"Failed to open scene: %s: %s\n"
# define CE_SCENE_READ			"Failed to read scene: %s\n\n"
# define CE_SCENE_LINE			"Scene parsing error at line %d: %s\n"
# define CE_SCENE_EMPTY			"Scene is empty"
# define CE_TEXTURE_PATH		"Invalid texture path"
# define CE_TEXTURE_DUP			"Duplicate texture assignment"
# define CE_PROP_UNKNOWN		"Unknown property"
# define CE_MAP_NONE			"No map found in scene"
# define CE_MAP_UNKOWN_OPT		"Unknown scene option"

typedef struct s_props	t_props;
typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_cub	t_cub;

struct s_props
{
	// not sure how to store images yet, probably an mlx thing
	// but for now let's just store the path
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		col_f[3];
	int		col_c[3];
};
struct s_map
{
	int		w;
	int		h;
	int		**blocks;
};
struct s_player
{
	float	x;
	float	y;
	float	rot;
};
struct s_cub
{
	t_props		props;
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
int		parse_scene(t_cub *cub, const char *map_path);
char	*get_line_start(char *line);
int		has_all_props(t_props *props);

// ----- //
// UTILS //
// ----- //
void	set_int_arr(int *arr, int size, int val);
void	free_props(t_props *props);
void	free_cub(t_cub *cub);

// TEST CODE REMOVE LATER -------------------------------------------------------
void	show_map(t_list *lst);
void	display_scene(t_cub *cub);

#endif

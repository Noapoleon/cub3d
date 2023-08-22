/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:43 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/22 03:58:33 by nlegrand         ###   ########.fr       */
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
# include "cub3d_err.h"

typedef struct e_blocktype	t_blocktype;
typedef struct s_props		t_props;
typedef struct s_map		t_map;
typedef struct s_player		t_player;
typedef struct s_cub		t_cub;

# define T_NONE	-1
# define T_AIR	0
# define T_WALL	1

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
	int		x_offset;
	int		**tiles;
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
char	*get_line_start(const char *line);
char	*get_line_end(const char *line);
int		has_all_props(t_props *props);
int		is_map_str(const char *s);
void	print_missing_props(t_props *prop);

// ----- //
// UTILS //
// ----- //
void	set_int_arr(int *arr, int size, int val);
void	free_props(t_props *props);
void	free_map(t_map *map);
void	free_cub(t_cub *cub);

// TEST CODE REMOVE LATER -------------------------------------------------------
void	show_map(t_list *lst);
void	display_scene(t_cub *cub);

#endif

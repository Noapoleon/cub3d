/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:43 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/20 21:03:59 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include "cub3d_err.h"

// SETTINGS
# define W_WIDTH		1600
# define W_HEIGHT		800
# define MOUSE_SPEED	1.0
# define PLAYER_SPEED	3.0 // blocks per second
# define PLAYER_REACH	4
# define RENDER_DIST	100.0 // secure later // try really low and really high or protect higher than would be 1 pixel
# define MULTITHREADING	0 // maybe do or not idk

// CONSTANTS
# define T_NONE			-1
# define T_AIR			0
# define T_WALL			1
# define T_WALL_ANIM	2
# define T_DOOR_C		3
# define T_DOOR_O		4
# define W_TITLE		"cub3d"

typedef struct s_sprite		t_sprite;
typedef struct s_texline	t_texline;
typedef struct s_vec2df		t_vec2df;
typedef struct s_vec2di		t_vec2di;
typedef struct s_ray		t_ray;
typedef struct s_inputs		t_inputs;
typedef struct s_imgmlx		t_imgmlx;
typedef struct s_texture	t_texture;
typedef struct s_mlx		t_mlx;
typedef struct s_props		t_props;
typedef struct s_map		t_map;
typedef struct s_player		t_player;
typedef struct s_cub		t_cub;

struct s_texline
{
	t_texture	*tex;
	int			height;
	int			h_mid;
	int			range[2];
	double		step[2];
	int			pos[2];
	double		fog;
};
struct s_vec2df
{
	double	x;
	double	y;
};
struct s_vec2di
{
	int	x;
	int	y;
};
struct s_ray
{
	t_vec2df	dir;
	t_vec2di	step;
	t_vec2df	step_dist;
	t_vec2di	map_check;
	t_vec2df	dist;
	double		last_dist;
	int			side; // remove? 0 to 3 for index in textures?? idk, -1 no walls
	int			tile_type;
	int			index;
	double		render_dist;
};
struct s_inputs
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	e;
	int	m;
	//int	shift; // later
	int	la;
	int	ra;
};
struct s_imgmlx
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		w;
	int		h;
};
struct s_texture
{
	char		*path;
	t_imgmlx	img;
	int			w;
	int			h;
};
struct s_sprite
{
	t_texture	tex;
	int			num_frames;
	t_texture	*frames;
	int			index;
	t_texture	*frame;
	long		delay; //usec
	long		elapsed;
};
struct s_mlx
{
	void		*ptr;
	void		*win;
	t_imgmlx	img;
	int			w;
	int			h;
	int			w_mid;
	int			h_mid;
	int			focused;
};
struct s_props
{
	// CHECK INIT FUNCTIONS FOR ALL STRUCTS
	t_texture	walls[4];
	t_texture	door[2];
	t_sprite	wall_anim;
	int			col_f;
	int			col_c;
};
struct s_map
{
	int		w;
	int		h;
	int		**tiles;
};
struct s_player
{
	t_vec2df	pos;
	double		rot;
	t_vec2df	dir;
	t_vec2df	cam;
	double		ratio_fix;
	int			*cursor;
};
struct s_cub
{
	t_props		props;
	t_map		map;
	t_player	player;
	t_mlx		mlx;
	t_inputs	inputs;
	long		delta;
	int			minimap;
};

// ---- //
// MAIN //
// ---- //
int		game_loop(t_cub *cub);

// ----- //
// SETUP //
// ----- //
// setup.c
int		setup_cub(t_cub *cub, int ac, char **av);
// setup_init.c
void	init_vars_props(t_props *props);
void	init_vars_map(t_map *map);
void	init_vars_player(t_player *player);
void	init_vars_mlx(t_mlx *mlx);
void	init_vars_inputs(t_inputs *inputs);
// setup_init_2.c
void	init_vars_imgmlx(t_imgmlx *img);
void	init_vars_texture(t_texture *t);
void	init_vars_sprite(t_sprite *s);
// setup_mlx.c
int		setup_mlx(t_cub *cub, t_mlx *mlx, t_props *props);

// ------ //
// PARSER //
// ------ //
// parser.c
int		parse_scene(t_cub *cub, const char *map_path);
// parser_read.c
int		check_map_path(const char *map_path);
int		read_map_file(const char *map_path, t_list **lines);
// parser_props.c
int		get_props(t_props *props, t_list **cur, int *count);
// parser_map.c
int		get_map(t_cub *cub, t_list *cur, int count);
// parser_utils.c
char	*get_line_start(const char *line);
char	*get_line_end(const char *line);
int		has_all_props(t_props *props);
int		is_map_str(const char *s);
void	print_missing_props(t_props *prop);
int		get_tile_val(char c);
int		check_airtile_surround(t_map *map, int x, int y);
void	alloc_map_size(t_map *map, int width, int height);

// ----- //
// UTILS //
// ----- //
// utils1.c
void	set_int_arr(int *arr, int size, int val);
void	get_deltatime(t_cub *cub);
double	get_principal_angle(double angle);
// utils_free.c
void	free_props(t_props *props);
void	free_map(t_map *map);
void	free_mlx(t_mlx *mlx, t_props *props);
void	free_cub(t_cub *cub);
// utils_vec.c
void	set_vec2df(t_vec2df *v, double x, double y);
void	set_vec2di(t_vec2di *v, int x, int y);
// utils_debug.c
void	print_fps(t_cub *cub);
void	print_mouse_pos(t_mlx *mlx);


// ----- //
// HOOKS //
// ----- //
// hooks.c
int		set_mlx_hooks(t_cub *cub, t_mlx *mlx);
int		keypress_hook(int keycode, t_cub *cub);
int		keyrelease_hook(int keycode, t_cub *cub);
// hooks_mouse.c
int		mouse_move_hook(int x, int y, t_cub *cub);

// ------- //
// GRAHICS //
// ------- //
// draw_utils.c
void	init_ray(t_ray *r, t_player *p, int	index);
int		ray_dda_loop(t_ray *r, t_cub *cub);
void	draw_frame(t_cub *cub, t_mlx *mlx, t_player *player);
// draw_vert_line.c
void	draw_vert_line(t_cub *cub, t_ray *r);
// graphic_utils.c
void	clear_imgmlx(t_cub *cub, int col);
void	set_imgmlx_data(t_imgmlx *img, int width, int height);
void	copy_frame(t_imgmlx *src, t_imgmlx *dst, int pos[2]);
void	copy_imgmlx(t_imgmlx *src, t_imgmlx *dst, int pos[2]);
int		open_texture(t_mlx *mlx, t_texture *t);
int		open_sprite(t_mlx *mlx, t_sprite *s, int delay);
void	set_pixel(t_imgmlx *img, int pos[2], int col);
int		get_pixel(t_imgmlx *img, int pos[2]);
void	set_rect(t_imgmlx *img, int pos[2], int size[2], int col);
void	refresh_sprite(t_cub *cub, t_sprite *s);

// handle_inputs.c
void	handle_inputs(t_cub *cub);


// TEST CODE REMOVE LATER -------------------------------------------------------
void	write_map(t_map *map);
void	display_scene(t_cub *cub);
void	display_map(t_cub *cub);
void	draw_square(t_cub *cub, int pos[2], int size, int col);
void	display_inputs(t_cub *cub, int pos[2]);
void	display_rot(t_cub *cub, int pos[2]);
void	display_movdir(t_cub *cub, int pos[2]);

// Features                                                                    remove
// w a s d	: move
// m		: toggle map
// mouse	: look around
// add ifndef for mac and dell keys

#endif

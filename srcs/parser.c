/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:18:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/23 05:51:28 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns 0 if map path is correct, returns -1 otherwise
// Format: <mapname>.cub
static int	check_map_path(const char *map_path)
{
	int	len;
	int	fd;

	if (map_path == NULL)
		return (ft_perr(CUB_ERR CE_SCENE_PATH_NULL), -1);
	len = ft_strlen(map_path);
	if (len < 5)
		return (ft_perr(CUB_ERR CE_SCENE_PATH_FORMAT), -1);
	if (ft_strncmp(&map_path[len - 4], ".cub\0", 5) != 0)
		return (ft_perr(CUB_ERR CE_SCENE_PATH_FORMAT), -1);
	fd = open(map_path, O_DIRECTORY);
	if (fd != -1)
		return (ft_perr(CUB_ERR CE_SCENE_OPEN, map_path, "Is a directory"),
				close(fd), -1);
	return (close(fd), 0);
}

// Reads map file lines one by one and stores them in a chained list
static int	read_map_file(const char *map_path, t_list **lines)
{
	int		fd;
	char	*line;
	t_list	*tmp;
	int		len;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (ft_perr(CUB_ERR CE_SCENE_OPEN, map_path, strerror(errno)), -1);
	while (gnl_w(fd, &line) == 0)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		tmp = ft_lstnew(line);
		if (tmp == NULL)
			return (ft_perr(CUB_ERR CE_SCENE_READ, strerror(errno)),
					ft_lstclear(lines, free), close(fd), -1);
		tmp->next = *lines;
		*lines = tmp;
	}
	ft_lstrev(lines);
	return (close(fd), 0);
}

static int	get_texture(char **dst, const char *src, int count)
{
	int	i;

	if (*dst)
		return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_TEXTURE_DUP), -1);
	i = 0;
	while (src[i] != ' ')
		++i;
	while (src[i] == ' ')
		++i;
	if (src[i] == '\0')
		return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_TEXTURE_PATH), -1);
	*dst = ft_strdup(src + i);
	if (*dst == NULL)
		return (ft_perr(CUB_ERR CE_SCENE_LINE, count, strerror(errno)), -1);
	return (0);
}

static int	get_8bit_col(const char *s, int *dst)
{
	int	i;
	int	n;

	if (!ft_isdigit(s[0]))
		return (-1);
	i = 0;
	while (ft_isdigit(s[i]))
		++i;
	if (i > 3)
		return (-1);
	n = ft_atoi(s);
	if (n < 0 || n > 255)
		return (-1);
	return ((*dst = n), i);
}
static int	get_color(int col[3], const char *tmp, int count)
{
	int	i;
	int	ret;
	int	j;

	i = 0;
	while (tmp[i] != ' ')
		++i;
	j = 0;
	while (j < 3)
	{
		while (tmp[i] == ' ')
			++i;
		ret = get_8bit_col(&tmp[i], &col[j]);
		if (ret == -1)
			return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_COL_FORMAT), -1);
		i += ret;
		while (tmp[i] == ' ')
			++i;
		if (j != 2 && tmp[i++] != ',')
			return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_COL_FORMAT), -1);
		++j;
	}
	return (0);
}

static int	get_prop(t_props *props, const char *tmp, int count)
{
	if (ft_strncmp("NO ", tmp, 3) == 0)
		return (get_texture(&props->no, tmp, count));
	else if (ft_strncmp("SO ", tmp, 3) == 0)
		return (get_texture(&props->so, tmp, count));
	else if (ft_strncmp("WE ", tmp, 3) == 0)
		return (get_texture(&props->we, tmp, count));
	else if (ft_strncmp("EA ", tmp, 3) == 0)
		return (get_texture(&props->ea, tmp, count));
	else if (ft_strncmp("F ", tmp, 2) == 0)
		return (get_color(props->col_f, tmp, count));
	else if (ft_strncmp("C ", tmp, 2) == 0)
		return (get_color(props->col_c, tmp, count));
	else
	{
		if (is_map_str(tmp))
			return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_PROP_MAP),
					print_missing_props(props), -1);
		else
			return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_PROP_UNKNOWN), -1);
	}
}

// Returns map start pointer
static int	get_props(t_props *props, t_list **cur, int *count)
{
	char	*tmp;

	while (*cur && !has_all_props(props))
	{
		tmp = get_line_start((*cur)->data);
		if (tmp[0] != '\0' && get_prop(props, tmp, *count) != 0) // CHECK AGAIN FOR OTHER OUTCOMES
			return (free_props(props), -1);
		++(*count);
		*cur = (*cur)->next;
	}
	return (0);
}

static void	alloc_map_size(t_map *map, int width, int height)
{
	int	i;

	if (width < 3 || height < 3)
		return ((void)ft_perr(CUB_ERR CE_MAP_SMALL));
	map->tiles = malloc(sizeof(*map->tiles) * height); // check if that's good for the sizeof
	if (map->tiles == NULL)
		return ((void)ft_perr(CUB_ERR CE_MAP_MALLOC, strerror(errno)));
	i = 0;
	while (i < height)
	{
		map->tiles[i] = malloc(sizeof(**map->tiles) * width); // sizeof not sure
		if (map->tiles[i] == NULL)
		{
			while (i--)
				free(map->tiles[i]);
			free(map->tiles);
			return ((void)ft_perr(CUB_ERR CE_MAP_MALLOC, strerror(errno)));
		}
		set_int_arr(map->tiles[i], width, -1);
		++i;
	}
	return ((map->w = width), (void)(map->h = height));
}

static int	alloc_map(t_map *map, t_list *cur, int count)
{
	int		min_width;
	int		max_width;
	int		height;
	char	*tmp;

	min_width = INT_MAX;
	max_width = -1;
	height = 0;
	while (cur)
	{
		++height;
		tmp = get_line_start(cur->data);
		if (tmp[0] != '\0')
		{
			if (!is_map_str(tmp))
				return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_MAP_CHAR), -1);
			map->h = height;
			min_width = ft_min(min_width, tmp - (char *)cur->data);
			tmp = get_line_end(cur->data);
			max_width = ft_max(max_width, tmp - (char *)cur->data);
		}
		cur = cur->next;
	}
	alloc_map_size(map, max_width - min_width, map->h);
	return ((map->x_offset = min_width), (map->tiles == NULL) * -1);
}

static int	get_tile_val(char c)
{
	if (c == ' ')
		return (-1);
	else if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (0);
	else
		return (1);
}

static int	set_player(t_player *player, int x, int y, char c)
{
	if (player->x != -1.0f)
		return (-1);
	player->x = (float)x + 0.5f;
	player->y = (float)y + 0.5f;
	if (c == 'N')
		player->rot = M_PI_2;
	else if (c == 'S')
		player->rot = -M_PI_2;
	else if (c == 'W')
		player->rot = M_PI;
	else
		player->rot = 0;
	return (0);
}

static int	fill_map(t_map *map, t_player *player, t_list *cur, int count)
{
	int		x;
	int		y;
	char	c;
	int		len_cur;

	y = 0;
	while (y < map->h)
	{
		++count;
		x = 0;
		len_cur = ft_strlen(cur->data);
		while (x < map->w && x < len_cur)
		{
			c = ((char *)cur->data)[map->x_offset + x];
			map->tiles[y][x] = get_tile_val(c);
			if (ft_isalpha(c) && set_player(player, x, y, c) != 0)
				return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_PLAYER_DUP),
						-1);
			++x;
		}
		cur = cur->next;
		++y;
	}
	if (player->x == -1.0f)
		return (ft_perr(CUB_ERR CE_PLAYER_NONE), -1);
	return (0);
}

static int	check_airtile_surround(t_map *map, int x, int y)
{
	int	**tiles;

	tiles = map->tiles;
	if (x == 0 || x == map->w - 1 || y == 0 || y == map->h - 1)
		return (-1);
	if (tiles[y][x - 1] == -1 || tiles[y][x + 1] == -1)
		return (-1);
	if (tiles[y - 1][x] == -1 || tiles[y + 1][x] == -1)
		return (-1);
	return (0);
}

static int	check_map(t_map *map, int count)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->h)
	{
		++count;
		x = 0;
		while (x < map->w)
		{
			if (map->tiles[y][x] == 0 && check_airtile_surround(map, x, y) != 0)
				return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_MAP_BAD), -1);
			++x;
		}
		++y;
	}
	return (0);
}

static int	get_map(t_map *map, t_player *player, t_list *cur, int count)
{
	char	*tmp;

	while (cur)
	{
		tmp = get_line_start(cur->data);
		if (tmp[0] != '\0')
			break ;
		cur = cur->next;
	}
	if (cur == NULL)
		return (ft_perr(CUB_ERR CE_MAP_NONE), -1);
	if (alloc_map(map, cur, count) != 0)
		return (-1);
	if (fill_map(map, player, cur, count) != 0)
		return (free_map(map), -1);
	if (check_map(map, count) != 0)
		return (free_map(map), -1); // free_allocated map
	return (0);
}

// Parses lines into map and player struct
// Returns 0 on success, or the line number in case of error
static int	parse_lines(t_props *props, t_map *map, t_player *player,
		t_list *lines)
{
	t_list	*cur;
	int		count;

	if (lines == NULL)
		return (ft_perr(CUB_ERR CE_SCENE_EMPTY), -1);
	cur = lines;
	count = 1;
	if (get_props(props, &cur, &count) != 0)
		return (-1);
	if (get_map(map, player, cur, count) != 0)
		return (free_props(props), -1);
	return (0);
}

// Reads the scene description file and stores all its properties in the map
// struct
// Returns 0 on success, -1 otherwise
int	parse_scene(t_cub *cub, const char *map_path)
{
	t_list	*lines;

	if (check_map_path(map_path) != 0)
		return (-1);
	lines = NULL;
	if (read_map_file(map_path, &lines) != 0)
		return (-1);
	if (parse_lines(&cub->props, &cub->map, &cub->player, lines) != 0)
		return (ft_lstclear(&lines, free), -1); // print line number error message
	ft_lstclear(&lines, free);
	return (0);
}

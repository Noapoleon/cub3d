/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:18:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/21 01:00:41 by nlegrand         ###   ########.fr       */
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
		//return (get_color(&props->col_f, tmp, count));
		return ((props->col_f[0] = 1), 0);
	else if (ft_strncmp("C ", tmp, 2) == 0)
		//return (get_color(&props->col_c, tmp, count));
		return ((props->col_c[0] = 1), 0);
	else
		return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_PROP_UNKNOWN), -1);
}

// Returns map start pointer
static int	get_props(t_props *props, t_list **cur, int *count)
{
	char	*tmp;

	while (*cur && !has_all_props(props))
	{
		tmp = get_line_start((*cur)->data);
		if (tmp[0] != '\0' && get_prop(props, tmp, *count) == -1) // CHECK AGAIN FOR OTHER OUTCOMES
			return (free_props(props), -1);
		++(*count);
		*cur = (*cur)->next;
	}
	return (0);
}

// Parses lines into map and player struct
// Returns 0 on success, or the line number in case of error
static int	parse_lines(t_props *props, t_map *map, t_player *player,
		t_list *lines)
{
	(void)map;  // remove
	(void)player;  // remove
	t_list	*cur;
	int		count;

	if (lines == NULL)
		return (ft_perr(CUB_ERR CE_SCENE_LINE, 0, CE_SCENE_EMPTY), -1); // test empty file
	cur = lines;
	count = 1;
	if (get_props(props, &cur, &count) != 0)
		return (-1);
	//if (cur == NULL)
	//	return (ft_perr(CUB_ERR CE_SCENE_LINE, count, CE_MAP_NONE),
	//			free_props(props), -1);
//	if (get_map(map, player, cur, &count) != 0)
//		return (free_props(props), -1);
	return (0);
}

// Reads the scene description file and stores all its properties in the map
// struct
// Returns 0 on success, -1 otherwise
int	parse_scene(t_cub *cub, const char *map_path)
{
	t_list	*lines;

	if (check_map_path(map_path) == -1)
		return (-1);
	lines = NULL;
	if (read_map_file(map_path, &lines) != 0)
		return (-1);
	if (parse_lines(&cub->props, &cub->map, &cub->player, lines) != 0)
		return (ft_lstclear(&lines, free), -1); // print line number error message
	ft_lstclear(&lines, free);
	return (0);
}

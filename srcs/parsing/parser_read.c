/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:14:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/22 13:57:03 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns 0 if map path is correct, returns -1 otherwise
// Format: <mapname>.cub
int	check_map_path(const char *map_path)
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
	return (0);
}

// Reads map file lines one by one and stores them in a chained list
int	read_map_file(const char *map_path, t_list **lines)
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

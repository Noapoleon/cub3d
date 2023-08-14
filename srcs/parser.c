/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:18:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/14 05:21:58 by nlegrand         ###   ########.fr       */
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
		return (print_err(CE_MAP_PATH_NULL), -1);
	len = ft_strlen(map_path);
	if (len < 5)
		return (print_err(CE_MAP_PATH_FORMAT), -1);
	if (ft_strncmp(&map_path[len - 4], ".cub\0", 5) != 0)
		return (print_err(CE_MAP_PATH_FORMAT), -1);
	fd = open(map_path, O_DIRECTORY);
	if (fd != -1)
		return (ft_dprintf(STDERR_FILENO, CUB_ERR CE_MAP_OPEN, map_path,
				"Is a directory"), close(fd), -1);
	close(fd);
	return (0);
}

// Reads map file lines one by one and stores them in a chained list
static int	read_map_file(const char *map_path, t_list **lines)
{
	int		fd;
	char	*line;
	t_list	*tmp;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (gnl_w(fd, &line) == 0)
	{
		tmp = ft_lstnew(line);
		if (tmp == NULL)
			return (ft_lstclear(lines, free), close(fd), -1);
		tmp->next = *lines;
		*lines = tmp;
	}
	ft_lstrev(lines);
	return (close(fd), 0);
}

// Reads the map file and stores all its properties in the map struct
// Returns 0 on success, -1 otherwise
int	parse_map(t_cub *cub, const char *map_path)
{
	t_list	*lines;

	if (check_map_path(map_path) == -1)
		return (-1);
	lines = NULL;
	if (read_map_file(map_path, &lines) == -1)
		return (ft_dprintf(STDERR_FILENO, CUB_ERR CE_MAP_READ,
				strerror(errno)), -1);
	(void)cub; // remove later
	ft_lstclear(&lines, free);
	return (0);
}

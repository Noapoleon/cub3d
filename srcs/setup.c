/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:45:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/01 19:13:22 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (print_err(CE_MAP_DIRECTORY), close(fd), -1);
	close(fd);
	return (0);
}

static int	parse_map(t_cub *cub, const char *map_path)
{
	(void)cub; // remove
	//int	fd;
	// map name ends in .cub
	if (check_map_path(map_path) == -1)
		return (-1);
	// open map if faile -1 and strerror and check it's not a directory
	//fd = open(map_path, O_RDONLY);
	//if (fd == -1)
	//	return (ft_dprintf(STDERR_FILENO, CUB_ERR CE_MAP_OPEN,
	//			strerror(errno)), -1);
	// parse map

	return (0);
}

int	setup_cub(t_cub *cub, int ac, char **av)
{
	(void)cub;
	(void)ac;
	(void)av;

	if (ac != 2)
		return (ft_dprintf(STDERR_FILENO, "Usage: %s <map.cub>\n", av[0]), -1);
	if (parse_map(cub, av[1]) == -1)
		return (-1);
	return (0);
}

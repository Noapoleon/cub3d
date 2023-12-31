/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:18:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/21 00:45:39 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Parses lines into map and player struct
// Returns 0 on success, or the line number in case of error
static int	parse_lines(t_cub *cub, t_list *lines)
{
	t_list	*cur;
	int		count;

	if (lines == NULL)
		return (ft_perr(CUB_ERR CE_SCENE_EMPTY), -1);
	cur = lines;
	count = 1;
	if (get_props(&cub->props, &cur, &count) != 0)
		return (-1);
	if (get_map(cub, cur, count) != 0)
		return (free_props(&cub->props), -1);
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
	if (parse_lines(cub, lines) != 0)
		return (ft_lstclear(&lines, free), -1);
	return (ft_lstclear(&lines, free), 0);
}

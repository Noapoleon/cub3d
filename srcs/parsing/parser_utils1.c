/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:25:34 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/19 16:57:23 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns address to first character of line that's not a space
char	*get_line_start(const char *line)
{
	int	i;

	if (line == NULL)
		return (NULL);
	i = 0;
	while (line[i] && line[i] == ' ')
		++i;
	return ((char *)(&line[i]));
}

char	*get_line_end(const char *line)
{
	int	i;

	if (line == NULL)
		return (NULL);
	i = ft_strlen(line);
	while (i != 0 && line[i - 1] == ' ')
		--i;
	return ((char *)(&line[i]));
}


// Checks t_props struct to see if all properties have been found
int	has_all_props(t_props *props)
{
	return (props->walls[0].path && props->walls[1].path
			&& props->walls[2].path && props->walls[3].path
			&& props->door[0].path && props->door[1].path
			&& props->wall_anim.tex.path
			&& props->col_f != -1 && props->col_c != -1);
}

// Loops through the string and checks if it only contains map characters
int	is_map_str(const char *s)
{
	int	i;

	i = 0;
	// torched walls	-> '2'
	// doors			-> '3'
	// opened doors		-> '4' (never present in parsing, all doors are closed by default)
	// doors need to be treated like air blocks for closed map check
	while (s[i])
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3'
			&& s[i] != ' ' && s[i] != 'N' && s[i] != 'S' && s[i] != 'E'
			&& s[i] != 'W')
			return (0);
		++i;
	}
	return (1);
}

// Prints missing properties after CE_PROP_MAP error
void	print_missing_props(t_props *prop)
{
	if (prop->walls[0].path == NULL)
		ft_printf(" - North texture\n");
	if (prop->walls[1].path == NULL)
		ft_printf(" - South texture\n");
	if (prop->walls[2].path == NULL)
		ft_printf(" - West texture\n");
	if (prop->walls[3].path == NULL)
		ft_printf(" - East texture\n");
	if (prop->col_f == -1)
		ft_printf(" - Floor color\n");
	if (prop->col_c == -1)
		ft_printf(" - Ceiling color\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:25:34 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/20 22:55:00 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns address to first character of line that's not a space
char	*get_line_start(char *line)
{
	int	i;

	if (line == NULL)
		return (NULL);
	i = 0;
	while (line[i] && line[i] == ' ')
		++i;
	return (&line[i]);
}

// Checks t_props struct to see if all properties have been found
int	has_all_props(t_props *props)
{
	return (props->no && props->so && props->we && props->ea && 
			props->col_f[0] != -1 && props->col_c[0] != -1);
}

// Loops through the string and checks if it only contains map characters
int	is_map_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != ' '
			&& s[i] != 'N' && s[i] != 'S' && s[i] != 'E' && s[i] != 'W')
			return (0);
		++i;
	}
	return (1);
}

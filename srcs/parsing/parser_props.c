/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_props.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:20:00 by nlegrand          #+#    #+#             */
/*   Updated: 2023/10/17 19:05:11 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Copies the texture path into dst
// All spaces after the identifier and initial space separation count towards
// the name of the file, meaning spaces at the end are not trimmed
static int	get_texture_path(char **dst, const char *src, int count)
{
	int	i;
	int	len;

	if (*dst)
		return (ft_perr(CUB_ERR CE_LINE, count, CE_TEXTURE_DUP), -1);
	i = 0;
	while (src[i] == ' ')
		++i;
	len = ft_strlen(src + i);
	if (len < 5)
		return (ft_perr(CUB_ERR CE_LINE, count, CE_TEXTURE_PATH), -1);
	if (ft_strncmp(&src[i + len - 4], ".xpm\0", 5) != 0)
		return (ft_perr(CUB_ERR CE_LINE, count, CE_TEXTURE_FORMAT), -1);
	*dst = ft_strdup(src + i);
	if (*dst == NULL)
		return (ft_perr(CUB_ERR CE_LINE, count, strerror(errno)), -1);
	return (0);
}

// Reads color substring and returns an error if not in range 0-255
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

// Gets all three numbers of RGB color line
static int	get_color(int *dst, const char *tmp, int count)
{
	int	i;
	int	ret;
	int	j;
	int	col[3];

	i = 0;
	j = 0;
	while (j < 3)
	{
		while (tmp[i] == ' ')
			++i;
		ret = get_8bit_col(&tmp[i], &col[j]);
		if (ret == -1)
			return (ft_perr(CUB_ERR CE_LINE, count, CE_COL_FORMAT), -1);
		i += ret;
		while (tmp[i] == ' ')
			++i;
		if (j != 2 && tmp[i++] != ',')
			return (ft_perr(CUB_ERR CE_LINE, count, CE_COL_FORMAT), -1);
		++j;
	}
	*dst = col[0] << 16 | col[1] << 8 | col[2];
	return (0);
}

// Figures out which property the line is
static int	get_prop(t_props *props, const char *tmp, int count)
{
	if (ft_strncmp("NO ", tmp, 3) == 0)
		return (get_texture_path(&props->walls[0].path, tmp + 3, count));
	else if (ft_strncmp("SO ", tmp, 3) == 0)
		return (get_texture_path(&props->walls[1].path, tmp + 3, count));
	else if (ft_strncmp("WE ", tmp, 3) == 0)
		return (get_texture_path(&props->walls[2].path, tmp + 3, count));
	else if (ft_strncmp("EA ", tmp, 3) == 0)
		return (get_texture_path(&props->walls[3].path, tmp + 3, count));
	else if (ft_strncmp("F ", tmp, 2) == 0)
		return (get_color(&props->col_f, tmp + 2, count));
	else if (ft_strncmp("C ", tmp, 2) == 0)
		return (get_color(&props->col_c, tmp + 2, count));
	else
	{
		if (is_map_str(tmp))
			return (ft_perr(CUB_ERR CE_LINE, count, CE_PROP_MAP),
					print_missing_props(props), -1);
		else
			return (ft_perr(CUB_ERR CE_LINE, count, CE_PROP_UNKNOWN), -1);
	}
}

// Returns map start pointer
int	get_props(t_props *props, t_list **cur, int *count)
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

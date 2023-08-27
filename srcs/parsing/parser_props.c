/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_props.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:20:00 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/26 17:07:01 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Copies the texture path into dst
static int	get_texture(char **dst, const char *src, int count)
{
	// check if it's an xpm texture or not
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

// Figures out which property the line is
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

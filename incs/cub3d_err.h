/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_err.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:28:17 by nlegrand          #+#    #+#             */
/*   Updated: 2023/08/23 05:44:29 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERR_H
# define CUB3D_ERR_H

// Main error string
# define CUB_ERR				"Error\n"

// Scene file
# define CE_SCENE_PATH_NULL		"Scene path is NULL\n"
# define CE_SCENE_PATH_FORMAT	"Scene path wrong format, \
file name must end with '.map'\n"
# define CE_SCENE_DIRECTORY		"Scene path is a directory\n"
# define CE_SCENE_OPEN			"Failed to open scene: %s: %s\n"
# define CE_SCENE_READ			"Failed to read scene: %s\n\n"

// Scene parsing
# define CE_SCENE_LINE		"Scene parsing error at line %d: %s\n"
# define CE_TEXTURE_PATH	"Invalid texture path"
# define CE_TEXTURE_DUP		"Duplicate texture assignment"
# define CE_PROP_UNKNOWN	"Unknown property"
# define CE_PROP_MAP		"Missing properties before map start"
# define CE_COL_FORMAT		"Bad color format"
# define CE_MAP_CHAR		"Bad map character"
# define CE_PLAYER_DUP		"Duplicate player location"
# define CE_MAP_BAD			"Invalid map shape"
# define CE_SCENE_EMPTY		"Scene is empty\n"
# define CE_MAP_NONE		"No map found in scene\n"
# define CE_MAP_SMALL		"Map too small\n"
# define CE_MAP_MALLOC		"Map alloc fail: %s\n"
# define CE_PLAYER_NONE		"No player found\n"

#endif

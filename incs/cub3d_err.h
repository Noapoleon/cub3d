/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_err.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:28:17 by nlegrand          #+#    #+#             */
/*   Updated: 2023/11/20 15:09:38 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERR_H
# define CUB3D_ERR_H

// Main error string
# define CUB_ERR				"Error\n"

// Settings errors
# define CE_BAD_RES			"Resolution cannot be inferior to 128x128 \
or superior to 4096x4096\n"
# define CE_BAD_MOUSESPEED	"Mouse speed must be positive\n"
# define CE_BAD_PLAYERSPEED	"Player speed must be positive\n"
# define CE_BAD_PLAYERREACH	"Player reach must be positive\n"
# define CE_BAD_RENDERDIST	"Render distance must be positive\n"

// Scene file
# define CE_SCENE_PATH_NULL		"Scene path is NULL\n"
# define CE_SCENE_PATH_FORMAT	"Scene path wrong format, \
file name must end with '.map'\n"
# define CE_SCENE_DIRECTORY		"Scene path is a directory\n"
# define CE_SCENE_OPEN			"Failed to open scene: %s: %s\n"
# define CE_SCENE_READ			"Failed to read scene: %s\n\n"

// Scene parsing
# define CE_LINE		"Scene parsing error at line %d: %s\n"
# define CE_TEXTURE_PATH	"Invalid texture path"
# define CE_TEXTURE_FORMAT	"Invalid texture format. Need XPM file"
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
# define CE_MAP_ALLOC		"Map alloc fail: %s\n"
# define CE_PLAYER_NONE		"No player found\n"

// MLX errors
# define CE_MLX_PTR			"Failed to initialize mlx\n"
# define CE_MLX_WIN			"Failed to create new mlx window\n"
# define CE_MLX_IMG			"Failed to create new mlx image\n"
# define CE_TEX_OPEN	"Failed to open/read texture `%s'\n"
# define CE_SPRITE_RES		"Sprite width is not multiple of its height\n"
# define CE_SPRITE_ALLOC	"Failed to allocate frames: `%s'\n"
# define CE_SPRITE_ALLOC	"Failed to allocate frames: `%s'\n"
# define CE_SPRITE_IMG		"Failed to create new sprite mlx image\n"

#endif

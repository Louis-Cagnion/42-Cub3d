/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/21 10:36:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_BONUS_H
# define MAP_BONUS_H

# include "libft.h"
# include "player_bonus.h"
# include "textures_bonus.h"

typedef struct s_minimap
{
	double	ratio_h;
	double	ratio_w;
	t_img	*mini_img;
	int		y_mini_img;
	int		x_mini_img;
	int		height_mini;
	int		width_mini;
	t_img	*player_img;
	int		player_img_w;
	int		player_img_h;
	double	h_player;
	double	w_player;
}	t_minimap;

typedef struct s_tile
{
	t_texture	*tex_list;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*floor_path;
	char		*ceil_path;
	char		*is_wall_str;
	int			f_rgb;
	int			c_rgb;
	int			is_wall;
}	t_tile;

typedef struct s_map
{
	t_texture	*tex_list;
	t_player	*player;
	t_tile		tiles[256];
	char		tile_defined[256];
	char		*map;
	char		**map_array;
	int			w_map;
	int			h_map;
	t_list		*entity_list;
	t_minimap	minimap;
}	t_map;

#endif

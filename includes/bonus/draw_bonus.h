/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/11 20:05:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_BONUS_H
# define DRAW_BONUS_H

typedef struct s_minimap
{
	t_img	*img;
	int		fract_of_h;
	int		start_y;
	int		end_y;
	int		height_mini;
	int		fract_of_w;
	int		start_x;
	int		end_x;
	int		width_mini;
	double	ratio_y;
	double	ratio_y_player;
	double	ratio_x;
	double	ratio_x_player;
	int		*color_str;
}	t_minimap;

typedef struct s_sprite_drawing
{
	double		step;
	double		ratio;
	int			delim_x_start;
	int			delim_x_end;
	int			delim_y_start;
	int			delim_y_end;
	double		start_tex_y;
	int			screen_x;
	int			sprite_height;
	double		tex_y;
	int			*tex_addr;
	int			*addr;
	int			cam_y;
}	t_sprite_drawing;

typedef struct s_plane_drawer
{
	double	ray_dirs[2];
	double	player_pos[2];
	double	floor_pos[2];
	double	real_pos[2];
	int		map_pos[2];
	double	*row_table;
	int		tile;
}	t_plane_drawer;

#endif

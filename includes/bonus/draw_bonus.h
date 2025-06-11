/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/11 20:47:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_BONUS_H
# define DRAW_BONUS_H

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

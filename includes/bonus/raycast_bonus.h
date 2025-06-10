/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/10 12:18:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_BONUS_H
# define RAYCAST_BONUS_H

typedef struct s_raycast
{
	int			tile;
	int			*addr;
	char		side;
	int			line_height;
	int			half_line_height;
	int			wall_pos[2];
	double		ray_dir[2];
	double		wall_dist;
	int			texture_x;
	int			size_line;
	int			fake_bpp;
	int			tex_fake_bpp;
	double		*row_dist_table;
	int			half_win_height;
	double		cam_x;
	int			cam_y;
	double		cam_x_step;
	double		*z_buffer;
}	t_raycast;

#endif
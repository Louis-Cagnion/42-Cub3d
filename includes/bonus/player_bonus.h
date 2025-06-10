/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/10 12:08:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_BONUS_H
# define PLAYER_BONUS_H

typedef struct s_player
{
	double		x;
	double		y;
	int			int_x;
	int			int_y;
	double		x_mantissa;
	double		y_mantissa;
	double		plane_x;
	double		plane_y;
	double		direction_x;
	double		direction_y;
	double		ray_dir_x[2];
	double		ray_dir_y[2];
	double		mvt_speed;
	double		inv_deter;
	int			cam_y;
	int			half_win_height;
}	t_player;

#endif
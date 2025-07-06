/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/07/06 18:05:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_BONUS_H
# define PLAYER_BONUS_H

# include "bonus/entities_bonus.h"

typedef struct s_weapon
{
	t_entity	default_sprite;
	t_entity	*shot_animation;
	t_entity	*reload_animation;
	int			atk_points;
}	t_weapon;

typedef struct s_weapon_wheel
{
	t_weapon	handgun;
	t_weapon	shotgun;
	t_weapon	minigun;
}	t_weapon_wheel;

typedef struct s_player
{
	double			x;
	double			y;
	int				int_x;
	int				int_y;
	double			x_mantissa;
	double			y_mantissa;
	double			plane_x;
	double			plane_y;
	double			direction_x;
	double			direction_y;
	double			ray_dir_x[2];
	double			ray_dir_y[2];
	double			mvt_speed;
	double			inv_deter;
	int				cam_y;
	int				half_win_height;
	t_weapon_wheel	weapons;
}	t_player;

#endif
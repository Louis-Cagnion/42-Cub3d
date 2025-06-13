/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/13 15:50:40 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_BONUS_H
# define PLAYER_BONUS_H

# ifndef P_HPS
#  define P_HPS		100
# endif

# ifndef P_ATK
#  define P_ATK		50
# endif

# ifndef E_HPS
#  define E_HPS		P_ATK
# endif

# ifndef E_ATK
#  define E_ATK		P_HPS / 5
# endif

typedef struct s_hp_bar
{
	double 	hp_ratio;
	int		start_w_hp;
	int		start_h_hp;
	t_img	*hp_bar;
	int		hp_bar_w;
	int		hp_bar_h;
	int		*pixels_hp_bar;
}	t_hp_bar;

typedef struct s_stats
{
	int 		hps;
	int			old_hps;
	int 		attack;
	t_hp_bar	hp_bar;
}	t_stats;

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
	t_stats		stats;
}	t_player;

#endif
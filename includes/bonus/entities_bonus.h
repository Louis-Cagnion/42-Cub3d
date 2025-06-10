/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/10 13:57:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_BONUS_H
# define ENTITIES_BONUS_H

# include "textures_bonus.h"
# include "player_bonus.h"
# include "libft.h"

typedef struct s_entity
{
	double		x;
	double		y;
	double		player_dist_x;
	double		player_dist_y;
	double		player_dist;
	double		draw_dir_x;
	double		draw_dir_y;
	int			screen_x;
	int			sprite_height;
	int			half_height;
	int			framerate;
	t_list		**invisible_parts;
	t_texture	tex;
	t_stats		stats;
}	t_entity;

#endif
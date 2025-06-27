/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_coming_for_you_jimmy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:24:07 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/27 13:34:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	im_coming_jimmy(char **map_array, t_entity *entity, t_tile tiles[256])
{
	t_entity	cpy;
	double		norm_dx;
	double		norm_dy;

	if (entity->player_dist == 0)
		return ;
	norm_dx = entity->player_dist_x / entity->player_dist;
	norm_dy = entity->player_dist_y / entity->player_dist;
	cpy = *entity;
	cpy.x -= norm_dx * entity->mvt_speed;
	cpy.y -= norm_dy * entity->mvt_speed;
	if (!tiles[(int)map_array[(int)(entity->y)][(int)(cpy.x)]].is_wall)
		entity->x = cpy.x;
	if (!tiles[(int)map_array[(int)(cpy.y)][(int)entity->x]].is_wall)
		entity->y = cpy.y;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:01:23 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/10 11:34:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_entities(t_list *entities, t_player player, t_opti_const consts)
{
	t_entity	*entity;

	while (entities)
	{
		entity = (t_entity *)entities->data;
		entity->player_dist_x = entity->x - player.x;
		entity->player_dist_y = entity->y - player.y;
		entity->player_dist = sqrt(entity->player_dist_x * entity->player_dist_x
				+ entity->player_dist_y * entity->player_dist_y);
		entity->draw_dir_x = player.inv_deter * (player.direction_y
				* entity->player_dist_x - player.direction_x
				* entity->player_dist_y);
		entity->draw_dir_y = player.inv_deter * (-player.plane_y
				* entity->player_dist_x + player.plane_x
				* entity->player_dist_y);
		entity->screen_x = (int)(consts.half_width
				* (1 + entity->draw_dir_x / entity->draw_dir_y));
		entity->sprite_height = abs((int)(WIN_HEIGHT / entity->draw_dir_y));
		entity->half_height = entity->sprite_height / 2;
		entities = entities->next;
		entity->stats.hps = E_HPS;
		entity->stats.attack = E_ATK;
	}
}

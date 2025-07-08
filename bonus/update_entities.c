/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:01:23 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/05 20:42:14 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	update_sprite_frame(t_entity *entity)
{
	t_sprite_frame	*frame;

	entity->frame_count++;
	if (entity->frame_count == entity->framerate)
	{
		entity->frame_count = 0;
		entity->frame_list = entity->frame_list->next;
		frame = (t_sprite_frame *)entity->frame_list->data;
		entity->cur_tex = frame->tex;
		entity->cur_invisible_parts = frame->invisible_parts;
	}
}

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
		entity->screen_x = (int)(consts.half_win_width
				* (1 + entity->draw_dir_x / entity->draw_dir_y));
		entity->sprite_height = abs((int)(WIN_HEIGHT / entity->draw_dir_y));
		entity->half_height = entity->sprite_height / 2;
		update_sprite_frame(entity);
		entities = entities->next;
	}
}

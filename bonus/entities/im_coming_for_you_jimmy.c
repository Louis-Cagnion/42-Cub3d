/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_coming_for_you_jimmy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:24:07 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/21 16:28:36 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	mobs_coming(t_list *entities, t_player player, t_opti_const consts)
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
	}
}

static void	compute_movement(t_player *cpy, int key)
{
	if (key == 'w')
	{
		cpy->x += cpy->direction_x * cpy->mvt_speed;
		cpy->y += cpy->direction_y * cpy->mvt_speed;
	}
	else if (key == 's')
	{
		cpy->x -= cpy->direction_x * cpy->mvt_speed;
		cpy->y -= cpy->direction_y * cpy->mvt_speed;
	}
	else if (key == 'd')
	{
		cpy->x -= cpy->direction_y * cpy->mvt_speed;
		cpy->y += cpy->direction_x * cpy->mvt_speed;
	}
	else if (key == 'a')
	{
		cpy->x += cpy->direction_y * cpy->mvt_speed;
		cpy->y -= cpy->direction_x * cpy->mvt_speed;
	}
}

void	actualise_player_pos(char **map_array, t_player *player,
		int key, t_tile tiles[256])
{
	t_player	cpy;

	cpy = *player;
	compute_movement(&cpy, key);
	if (!tiles[(int)map_array[player->int_y][(int)(cpy.x)]].is_wall)
	{
		player->x = cpy.x;
		player->int_x = (int)cpy.x;
		player->x_mantissa = cpy.x - (int)cpy.x;
	}
	if (!tiles[(int)map_array[(int)cpy.y][(player->int_x)]].is_wall)
	{
		player->y = cpy.y;
		player->int_y = (int)cpy.y;
		player->y_mantissa = cpy.y - (int)cpy.y;
	}
}

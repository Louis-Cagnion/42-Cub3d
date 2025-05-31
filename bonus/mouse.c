/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:01:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/31 19:02:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	game->mouse.delta_x = x - game->consts.half_width;
	return (0);
}

void	actualise_cam_mouse(t_mouse *mouse, int mid_width, t_player *player)
{
	double	rotation;
	double	temp;

	rotation = mouse->delta_x * ROT_SPEED / (double)mid_width;
	if (rotation)
	{
		temp = player->direction_x;
		player->direction_x = temp * cos(rotation)
			- player->direction_y * sin(rotation);
		player->direction_y = temp * sin(rotation)
			+ player->direction_y * cos(rotation);
		temp = player->plane_x;
		player->plane_x = temp * cos(rotation)
			- player->plane_y * sin(rotation);
		player->plane_y = temp * sin(rotation)
			+ player->plane_y * cos(rotation);
		update_player_ray_dirs(player);
	}
}

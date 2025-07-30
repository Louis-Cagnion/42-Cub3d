/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:27:00 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/30 19:11:09 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	open_sesame(t_game *game)
{
	t_wall_drawer	drawer;

	ray_dirs[0] = game->player.direction_x;
	ray_dirs[0] = game->player.direction_y;
	target_x = game->player.int_x;
	target_y = game->player.int_y;
	side = side_dist[0] >= side_dist[1];
	drawer.map_pos[drawer.side] += drawer.steps[drawer.side];
}

int	pressed_mouse(int key, t_game *game)
{
	if (key == 1)
		if (open_sesame(game))
			return (0);
	return (0);
}

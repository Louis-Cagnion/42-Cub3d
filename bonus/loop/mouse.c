/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:27:00 by gakarbou          #+#    #+#             */
/*   Updated: 2025/08/03 17:34:15 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	open_sesame(t_game *game, t_map *map)
{
	t_wall_drawer	res;
	t_wall_drawer	consts;
	int				range;
	int				i;

	consts = init_ray_consts(&game->player, 0);
	res = cast_ray(consts, game, NULL, 1);
	range = 2;
	i = -1;
	while (++i < range)
	{
		res = cast_ray(consts, game, NULL, i);
		if (map->tiles[map->map_array[res.map_pos[1]][res.map_pos[0]]].is_door)
		{
			map->door_array[res.map_pos[1]][res.map_pos[0]] ^= 1;
			return (1);
		}
	}
	return (1);
}

int	pressed_mouse(int key, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (key == 1)
		if (open_sesame(game, &game->map))
			return (0);
	return (0);
}

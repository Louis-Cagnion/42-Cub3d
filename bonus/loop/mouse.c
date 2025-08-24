/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:27:00 by gakarbou          #+#    #+#             */
/*   Updated: 2025/08/24 18:58:28 by gakarbou         ###   ########.fr       */
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
		if (map->tiles[(int)
				map->map_array[res.map_pos[1]][res.map_pos[0]]].is_door)
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

int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = 1;

	if (x < last_x)
		game->player.rotation = (-ROT_SPEED * 1.5);
	else if (x > last_x)
		game->player.rotation = (ROT_SPEED * 1.5);
	if (x <= 10)
		mlx_mouse_move(game->mlx.init, game->mlx.window, WIN_WIDTH - 11, y);
	else if (x > (WIN_WIDTH - 10))
		mlx_mouse_move(game->mlx.init, game->mlx.window, 11, y);
	last_x = x;
	return (0);
}

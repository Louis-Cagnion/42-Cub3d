/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:49:22 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/19 22:52:27 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	init_steps_infos(t_player player, double ray_dir[2],
		double side_dist[2], int steps[2])
{
	steps[0] = -1;
	side_dist[0] = player.x_mantissa;
	if (ray_dir[0] >= 0)
	{
		steps[0] = 1;
		side_dist[0] = 1 - side_dist[0];
	}
	steps[1] = -1;
	side_dist[1] = player.y_mantissa;
	if (ray_dir[1] >= 0)
	{
		steps[1] = 1;
		side_dist[1] = 1 - side_dist[1];
	}
}

static inline void	init_delta_infos(t_player player,
		double ray_dir[2], double delta_dist[2], int map_pos[2])
{
	map_pos[0] = player.int_x;
	map_pos[1] = player.int_y;
	delta_dist[0] = 1000;
	if (ray_dir[0])
		delta_dist[0] = fabs(1 / ray_dir[0]);
	delta_dist[1] = 1000;
	if (ray_dir[1])
		delta_dist[1] = fabs(1 / ray_dir[1]);
}

static inline int	hit_wall(int tile, t_map *map, double side_dist[2], int is_vert, double delta_dist[2])
{
	double	dist;

	if (map->tiles[tile].is_wall && tile != '2')
		return (1);
	if (tile != '2')
		return (0);
	return (side_dist[!is_vert] >= (side_dist[is_vert] - (delta_dist[is_vert] * 0.5)));
}

double	get_wall_dist(t_player player, t_cast_infos *infos,
		double cam_x, t_map *map)
{
	int		is_vert;
	int		steps[2];
	int		map_pos[2];
	double	side_dist[2];
	double	delta_dist[2];

	infos->ray_dir[0] = player.direction_x + player.plane_x * cam_x;
	infos->ray_dir[1] = player.direction_y + player.plane_y * cam_x;
	init_delta_infos(player, infos->ray_dir, delta_dist, map_pos);
	init_steps_infos(player, infos->ray_dir, side_dist, steps);
	side_dist[0] *= delta_dist[0];
	side_dist[1] *= delta_dist[1];
	is_vert = 0;
	while (1)
	{
		is_vert = side_dist[0] >= side_dist[1];
		side_dist[is_vert] += delta_dist[is_vert];
		map_pos[is_vert] += steps[is_vert];
		if (map_pos[1] < 0 || map_pos[0] < 0 || map_pos[0] >= map->w_map
				|| map_pos[1] >= map->h_map)
			return (-1);
		if (hit_wall(map->map_array[map_pos[1]][map_pos[0]], map, side_dist, is_vert, delta_dist))
			break ;
	}
	infos->is_side = is_vert;
	infos->tile = map->map_array[map_pos[1]][map_pos[0]];
	if (infos->tile != '2')
		return (side_dist[is_vert] - delta_dist[is_vert]);
	return (side_dist[is_vert] - (0.5 * delta_dist[is_vert]));
}

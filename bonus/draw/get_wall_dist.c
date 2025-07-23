/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:49:22 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/23 18:39:25 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	init_steps_infos(t_player *player, double ray_dir[2],
		double side_dist[2], int steps[2])
{
	steps[0] = -1;
	side_dist[0] = player->x_mantissa;
	if (ray_dir[0] >= 0)
	{
		steps[0] = 1;
		side_dist[0] = 1 - side_dist[0];
	}
	steps[1] = -1;
	side_dist[1] = player->y_mantissa;
	if (ray_dir[1] >= 0)
	{
		steps[1] = 1;
		side_dist[1] = 1 - side_dist[1];
	}
}

static inline void	init_consts(t_wall_drawer *drawer, t_player *player, double cam_x)
{
	drawer->ray_dir[0] = player->direction_x + player->plane_x * cam_x;
	drawer->ray_dir[1] = player->direction_y + player->plane_y * cam_x;
	drawer->map_pos[0] = player->int_x;
	drawer->map_pos[1] = player->int_y;
	drawer->delta_dist[0] = 1000;
	if (drawer->ray_dir[0])
		drawer->delta_dist[0] = fabs(1 / drawer->ray_dir[0]);
	drawer->delta_dist[1] = 1000;
	if (drawer->ray_dir[1])
		drawer->delta_dist[1] = fabs(1 / drawer->ray_dir[1]);
	init_steps_infos(player, drawer->ray_dir, drawer->side_dist, drawer->steps);
	drawer->side_dist[0] *= drawer->delta_dist[0];
	drawer->side_dist[1] *= drawer->delta_dist[1];
	drawer->side = 0;
}

static inline int	draw_tex(t_wall_drawer *drawer, t_game *game)
{
	int		ret;
	int		tex_x;

	drawer->wall_dist = drawer->side_dist[drawer->side]
		- drawer->delta_dist[drawer->side];
	drawer->wall_x = game->player.y * !drawer->side + game->player.x * drawer->side
		+ drawer->wall_dist * drawer->ray_dir[!drawer->side];
	drawer->wall_x -= (int)drawer->wall_x;
	tex_x = drawer->wall_x * drawer->tex.d_width;
	if ((!drawer->side && drawer->ray_dir[0] > 0)
			|| (drawer->side && drawer->ray_dir[1] < 0))
		tex_x = drawer->tex.width - tex_x - 1;
	tex_x = (drawer->tex.width - tex_x - 1) * drawer->tex.fake_bpp;
	ret = drawer->tex.stripe_is_opaque[tex_x];
	return (ret);
}

static inline void	cast_ray(t_wall_drawer *drawer, t_game *game)
{
	t_map	*map;

	map = &game->map;
	while (1)
	{
		drawer->side = drawer->side_dist[0] >= drawer->side_dist[1];
		drawer->side_dist[drawer->side] += drawer->delta_dist[drawer->side];
		drawer->map_pos[drawer->side] += drawer->steps[drawer->side];
		if (drawer->map_pos[1] < 0 || drawer->map_pos[0] < 0
			 || drawer->map_pos[0] >= map->w_map || drawer->map_pos[1] >= map->h_map)
			return ;
		drawer->tile = map->map_array[drawer->map_pos[1]][drawer->map_pos[1]];
		if (map->tiles[drawer->tile].is_wall)
		{
			drawer->tex = map->tiles[drawer->tile].tex_list[(!drawer->side * 2)
				+ (drawer->ray_dir[drawer->side] < 0)];
			if (!draw_tex(drawer, game))
				return ;
		}
	}
}

double	get_wall_dist(t_player *player,
		double cam_x, t_game *game)
{
	t_wall_drawer	drawer;

	init_consts(&drawer, player, cam_x);
	cast_ray(&drawer, game);
	return (0);
}

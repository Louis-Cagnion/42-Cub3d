/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:49:22 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/30 19:10:59 by gakarbou         ###   ########.fr       */
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

static inline void	draw_texture(int *addr, t_wall_drawer *drawer, t_texture *tex,
	int size_line)
{
	int		*data;
	int		*addr_two;
	double	tex_pos[2];
	double	step;
	int		tex_size_line;
	int		color;
	int		temp;

	step = tex->d_height / drawer->line_height;
	tex_pos[0] = (drawer->wall_pos[0] - drawer->half_win_height
			+ drawer->half_line_height - drawer->cam_y) * step;
	temp = ((drawer->wall_pos[1] - drawer->wall_pos[0]) >> 1) + 1;
	data = (int *)(tex->data + drawer->texture_x);
	tex_size_line = tex->size_line >> 2;
	addr_two = addr + size_line * drawer->wall_pos[1];
	tex_pos[1] = tex_pos[0] + (step * (temp << 1));
	addr += size_line * drawer->wall_pos[0];
	while (temp--)
	{
		color = *(data + ((int)tex_pos[0] * tex_size_line));
		if (color >= 0)
			*addr = color;
		color = *(data + ((int)tex_pos[1] * tex_size_line));
		if (color >= 0)
			*addr_two = color;
		tex_pos[0] += step;
		tex_pos[1] -= step;
		addr += size_line;
		addr_two -= size_line;
	}
}

static inline void	cast_ray(t_wall_drawer drawer, t_game *game, int *addr);
static inline int	draw_tex(t_wall_drawer *drawer, t_game *game, int *addr)
{
	int		tex_x;

	drawer->wall_dist = drawer->side_dist[drawer->side]
		- (drawer->delta_dist[drawer->side] * game->map.tiles[drawer->tile].is_wall);
	drawer->wall_x = (game->player.y * !drawer->side + game->player.x * drawer->side)
		+ drawer->wall_dist * drawer->ray_dir[!drawer->side];
	drawer->wall_x -= (int)drawer->wall_x;
	tex_x = drawer->wall_x * drawer->tex.d_width;
	if ((!drawer->side && drawer->ray_dir[0] > 0)
			|| (drawer->side && drawer->ray_dir[1] < 0))
		tex_x = drawer->tex.width - tex_x - 1;
	tex_x = (drawer->tex.width - tex_x - 1);
	drawer->texture_x = tex_x * drawer->tex.fake_bpp;
	if (drawer->tex.stripe_is_opaque[tex_x])
		cast_ray(*drawer, game, addr);
	drawer->line_height = WIN_HEIGHT / drawer->wall_dist;
	drawer->half_line_height = drawer->line_height >> 1;
	drawer->wall_pos[0] = game->consts->half_win_height - drawer->half_line_height
		+ game->player.cam_y;
	drawer->wall_pos[1] = drawer->wall_pos[0] + (drawer->half_line_height << 1);
	if (drawer->wall_pos[0] >> 31)
		drawer->wall_pos[0] = 0;
	if (drawer->wall_pos[1] > WIN_HEIGHT)
		drawer->wall_pos[1] = WIN_HEIGHT;
	drawer->half_win_height = game->consts->half_win_height;
	drawer->cam_y = game->player.cam_y;
	draw_texture(addr, drawer, &drawer->tex, game->consts->size_line);
}

static inline int	hit_wall(int side, double side_dist[2], double delta_dist[2], double depth)
{
	return (side_dist[!side] >= (side_dist[side] - (delta_dist[side] * depth)));
}

static inline t_wall_drawer cast_ray(t_wall_drawer drawer, t_game *game, int *addr, int door)
{
	t_map	*map;

	map = &game->map;
	while (1)
	{
		drawer.side = drawer.side_dist[0] >= drawer.side_dist[1];
		drawer.side_dist[drawer.side] += drawer.delta_dist[drawer.side];
		drawer.map_pos[drawer.side] += drawer.steps[drawer.side];
		if (drawer.map_pos[1] < 0 || drawer.map_pos[0] < 0
			 || drawer.map_pos[0] >= map->w_map || drawer.map_pos[1] >= map->h_map)
			return (drawer);
		drawer.tile = map->map_array[drawer.map_pos[1]][drawer.map_pos[0]];
		if (map->tiles[drawer.tile].is_wall && hit_wall(drawer.side, drawer.side_dist, drawer.delta_dist, map->tiles[drawer.tile].is_wall))
		{
			drawer.tex = map->tiles[drawer.tile].tex_list[(!drawer.side * 2)
				+ (drawer.ray_dir[drawer.side] < 0)];
			draw_tex(&drawer, game, addr);
			return (drawer);
		}
		if (door)
			return (drawer);
	}
	return (drawer);
}

double	get_wall_dist(t_player *player,
		double cam_x, t_game *game, int *addr)
{
	t_wall_drawer	drawer;

	init_consts(&drawer, player, cam_x);
	cast_ray(drawer, game, addr);
	return (1);
}

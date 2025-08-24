/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:49:22 by gakarbou          #+#    #+#             */
/*   Updated: 2025/08/24 18:17:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	draw_texture(int *addr, t_wall_drawer *drawer,
		t_texture *tex, int size_line)
{
	t_draw	d;

	d = (t_draw){0};
	d.step = tex->d_height / drawer->line_height;
	d.tex_pos[0] = (drawer->wall_pos[0] - drawer->half_win_height
			+ drawer->half_line_height - drawer->cam_y) * d.step;
	d.temp = ((drawer->wall_pos[1] - drawer->wall_pos[0]) >> 1) + 1;
	d.data = (int *)(tex->data + drawer->texture_x);
	d.addr_two = addr + size_line * drawer->wall_pos[1];
	d.tex_pos[1] = d.tex_pos[0] + (d.step * (d.temp << 1));
	addr += size_line * drawer->wall_pos[0];
	while (d.temp--)
	{
		drawer->color = *(d.data + ((int)d.tex_pos[0] * tex->tex_size_line));
		if (drawer->color >= 0)
			*addr = drawer->color;
		drawer->color = *(d.data + ((int)d.tex_pos[1] * tex->tex_size_line));
		if (drawer->color >= 0)
			*d.addr_two = drawer->color;
		d.tex_pos[0] += d.step;
		d.tex_pos[1] -= d.step;
		addr += size_line;
		d.addr_two -= size_line;
	}
}

static inline void	draw_tex(t_wall_drawer *dr, t_game *game,
		int *addr, int tex_x)
{
	dr->wall_dist = dr->side_dist[dr->side]
		- (dr->delta_dist[dr->side] * game->map.tiles[dr->tile].is_wall);
	dr->wall_x = (game->player.y * !dr->side + game->player.x * dr->side)
		+ dr->wall_dist * dr->ray_dir[!dr->side];
	dr->wall_x -= (int)dr->wall_x;
	tex_x = dr->wall_x * dr->tex.d_width;
	if ((!dr->side && dr->ray_dir[0] > 0)
		|| (dr->side && dr->ray_dir[1] < 0))
		tex_x = dr->tex.width - tex_x - 1;
	tex_x = (dr->tex.width - tex_x - 1);
	dr->texture_x = tex_x * dr->tex.fake_bpp;
	if (dr->tex.stripe_is_opaque[tex_x])
		cast_ray(*dr, game, addr, 0);
	dr->line_height = WIN_HEIGHT / dr->wall_dist;
	dr->half_line_height = dr->line_height >> 1;
	dr->wall_pos[0] = game->consts->half_win_height - dr->half_line_height
		+ game->player.cam_y;
	dr->wall_pos[1] = dr->wall_pos[0] + (dr->half_line_height << 1);
	if (dr->wall_pos[0] >> 31)
		dr->wall_pos[0] = 0;
	if (dr->wall_pos[1] > WIN_HEIGHT)
		dr->wall_pos[1] = WIN_HEIGHT;
	dr->half_win_height = game->consts->half_win_height;
	dr->cam_y = game->player.cam_y;
	draw_texture(addr, dr, &dr->tex, game->consts->size_line);
}

static inline int	hit_wall(int side, double side_dist[2],
		double delta_dist[2], double depth)
{
	return (side_dist[!side] >= (side_dist[side] - (delta_dist[side] * depth)));
}

t_wall_drawer	cast_ray(t_wall_drawer drawer, t_game *game,
		int *addr, int door)
{
	t_map	*map;

	map = &game->map;
	while (1)
	{
		drawer.side = drawer.side_dist[0] >= drawer.side_dist[1];
		drawer.side_dist[drawer.side] += drawer.delta_dist[drawer.side];
		drawer.map_pos[drawer.side] += drawer.steps[drawer.side];
		if (!door-- || drawer.map_pos[1] < 0 || drawer.map_pos[0] < 0
			|| drawer.map_pos[0] >= map->w_map
			|| drawer.map_pos[1] >= map->h_map)
			return (drawer);
		drawer.tile = map->map_array[drawer.map_pos[1]][drawer.map_pos[0]];
		if (door < 0 && map->tiles[drawer.tile].is_wall
			&& hit_wall(drawer.side, drawer.side_dist, drawer.delta_dist,
				map->tiles[drawer.tile].is_wall))
		{
			drawer.tex = map->tiles[drawer.tile].tex_list[(!drawer.side * 2)
				+ (drawer.ray_dir[drawer.side] < 0)];
			draw_tex(&drawer, game, addr, 0);
			return (drawer);
		}
	}
	return (drawer);
}

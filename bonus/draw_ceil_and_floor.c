/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_and_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:13:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/02 16:30:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	init_loop_infos(t_plane_drawer *drawer,
		double row_dist, t_map map)
{
	drawer->floor_pos[0] = drawer->player_pos[0]
		+ row_dist * drawer->ray_dirs[0];
	drawer->floor_pos[1] = drawer->player_pos[1]
		+ row_dist * drawer->ray_dirs[1];
	drawer->map_pos[0] = (int)drawer->floor_pos[0];
	drawer->map_pos[1] = (int)drawer->floor_pos[1];
	drawer->tile = map.map_array[drawer->map_pos[1]][drawer->map_pos[0]];
	drawer->real_pos[0] = drawer->floor_pos[0] - drawer->map_pos[0];
	drawer->real_pos[1] = drawer->floor_pos[1] - drawer->map_pos[1];
}

static inline void	init_drawer_consts(t_plane_drawer *drawer, t_raycast *ray,
		t_map map, int *y)
{
	drawer->ray_dirs[0] = map.player->ray_dir_x[0]
		+ ray->cam_x * map.player->ray_dir_x[1];
	drawer->ray_dirs[1] = map.player->ray_dir_y[0]
		+ ray->cam_x * map.player->ray_dir_y[1];
	drawer->player_pos[0] = map.player->x;
	drawer->player_pos[1] = map.player->y;
	drawer->row_table = ray->row_dist_table
		+ (ray->half_win_height - ray->wall_pos[0] + ray->cam_y);
	*y = ft_min(ray->wall_pos[0], WIN_HEIGHT - ray->wall_pos[1] + 1);
}

static inline void	draw_extra_floor(int *addr, t_plane_drawer dr,
		t_raycast *ray, t_map map)
{
	t_texture	tex;
	int			height;
	int			size_line;
	double		*row_table;

	height = WIN_HEIGHT - (ray->wall_pos[1] + ray->wall_pos[0]);
	size_line = ray->size_line;
	row_table = ray->row_dist_table
		+ (ray->half_win_height - ray->cam_y - height);
	while (height--)
	{
		init_loop_infos(&dr, *(++row_table), map);
		tex = map.tiles[dr.tile].tex_list[4];
		*addr = ((int *)tex.data)[((int)(dr.real_pos[1] * tex.height)
				*tex.fake_size_line + ((int)(dr.real_pos[0] * tex.width)))];
		addr += size_line;
	}
}

static inline void	draw_extra_ceil(int *addr, t_plane_drawer dr,
		t_raycast *ray, t_map map)
{
	t_texture	tex;
	int			height;
	int			size_line;
	double		*row_table;

	height = ray->wall_pos[0] - (WIN_HEIGHT - ray->wall_pos[1]);
	size_line = ray->size_line;
	row_table = ray->row_dist_table + (ray->half_win_height + ray->cam_y);
	while (height--)
	{
		init_loop_infos(&dr, *(row_table--), map);
		tex = map.tiles[dr.tile].tex_list[5];
		*addr = ((int *)tex.data)[((int)(dr.real_pos[1] * tex.height)
				*tex.fake_size_line + ((int)(dr.real_pos[0] * tex.width)))];
		addr += size_line;
	}
}

void	draw_ceil_and_floor_tex(int *addr, int size_line,
		t_map map, t_raycast *ray)
{
	t_plane_drawer	dr;
	t_texture		tex;
	int				y;
	int				*ceil_addr;
	int				*floor_addr;

	floor_addr = addr + ray->wall_pos[1] * size_line;
	ceil_addr = addr + ray->wall_pos[0] * size_line;
	init_drawer_consts(&dr, ray, map, &y);
	while (y--)
	{
		init_loop_infos(&dr, *(++dr.row_table), map);
		tex = map.tiles[dr.tile].tex_list[5];
		*ceil_addr = ((int *)tex.data)[((int)(dr.real_pos[1] * tex.height)
				*tex.fake_size_line + ((int)(dr.real_pos[0] * tex.width)))];
		tex = map.tiles[dr.tile].tex_list[4];
		*floor_addr = ((int *)tex.data)[((int)(dr.real_pos[1] * tex.height)
				*tex.fake_size_line + ((int)(dr.real_pos[0] * tex.width)))];
		ceil_addr -= size_line;
		floor_addr += size_line;
	}
	if (ray->cam_y >> 31)
		draw_extra_floor(floor_addr, dr, ray, map);
	else if (ray->cam_y)
		draw_extra_ceil(addr, dr, ray, map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_and_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:13:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/08 13:51:24 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline double	**init_ray_dirs(t_raycast *infos, int width, t_player *player)
{
	double	**dest;
	double	cam_x;
	int		i;

	dest = malloc(sizeof(double *) * width);
	cam_x = infos->cam_x;
	i = 0;
	while (width--)
	{
		dest[i] = malloc(sizeof(double) * 2);
		dest[i][0] = player->ray_dir_x[0]
			+ cam_x * player->ray_dir_x[1];
		dest[i][1] = player->ray_dir_y[0]
			+ cam_x * player->ray_dir_y[1];
		i++;
		cam_x += infos->consts->cam_x_step;
	}
	return (dest);
}

static inline int	init_loop_infos(t_plane_drawer *drawer,
		double row_dist, t_map *map)
{
	drawer->floor_pos[1] = drawer->player_pos[1]
		+ row_dist * drawer->ray_dirs[1];
	drawer->floor_pos[0] = drawer->player_pos[0]
		+ row_dist * drawer->ray_dirs[0];
	drawer->map_pos[1] = (int)drawer->floor_pos[1];
	drawer->map_pos[0] = (int)drawer->floor_pos[0];
	if (drawer->map_pos[1] >= map->h_map || drawer->map_pos[0] >= map->w_map
		|| drawer->floor_pos[1] < 0 || drawer->floor_pos[0] < 0)
		return (1);
	drawer->tile = map->map_array[drawer->map_pos[1]][drawer->map_pos[0]];
	drawer->real_pos[0] = drawer->floor_pos[0] - drawer->map_pos[0];
	drawer->real_pos[1] = drawer->floor_pos[1] - drawer->map_pos[1];
	return (0);
}

static inline void	init_drawer_consts(t_plane_drawer *drawer, t_raycast *ray,
		t_map *map)
{
	drawer->ray_dirs[0] = map->player->ray_dir_x[0]
		+ ray->cam_x * map->player->ray_dir_x[1];
	drawer->ray_dirs[1] = map->player->ray_dir_y[0]
		+ ray->cam_x * map->player->ray_dir_y[1];
	drawer->player_pos[0] = map->player->x;
	drawer->player_pos[1] = map->player->y;
	drawer->row_table = ray->consts->row_dist_table
		+ (ray->cam_y);
	drawer->y = ray->consts->half_win_height;
}

static inline void	draw_extra_floor(int *addr, t_plane_drawer dr,
		t_raycast *ray, t_map *map)
{
	t_texture	tex;
	int			height;
	int			size_line;
	int			color;
	double		*row_table;

	(void)row_table;
	height = WIN_HEIGHT - (ray->wall_pos[1] + ray->wall_pos[0]);
	size_line = ray->consts->size_line;
	row_table = ray->consts->row_dist_table
		+ (ray->consts->half_win_height - ray->cam_y - height);
	while (height--)
	{
		tex = map->tiles[dr.tile].tex_list[4];
		color = ((int *)tex.data)[((int)(dr.real_pos[1] * tex.height)
				*tex.fake_size_line + ((int)(dr.real_pos[0] * tex.width)))];
		if (!(color >> 31))
			*addr = color;
		addr += size_line;
	}
}

static inline void	draw_extra_ceil(int *addr, t_plane_drawer dr,
		t_raycast *ray, t_map *map)
{
	t_texture	tex;
	int			height;
	int			size_line;
	int			color;
	double		*row_table;

	height = ray->wall_pos[0] - (WIN_HEIGHT - ray->wall_pos[1]);
	size_line = ray->consts->size_line;
	row_table = ray->consts->row_dist_table + (ray->consts->half_win_height + ray->cam_y);
	while (height--)
	{
		init_loop_infos(&dr, *(row_table--), map);
		tex = map->tiles[dr.tile].tex_list[5];
		color = ((int *)tex.data)[((int)(dr.real_pos[1] * tex.height)
				*tex.fake_size_line + ((int)(dr.real_pos[0] * tex.width)))];
		if (!(color >> 31))
			*addr = color;
		addr += size_line;
	}
}

void	draw_ceil_and_floor_tex(int *addr, int size_line,
		t_map *map, t_raycast *ray, int width)
{
	t_plane_drawer	dr;
	t_texture		tex;
	int				color;
	int				*ceil_addr;
	int				*floor_addr;
	int				i;
	double			**ray_dirs;

	init_drawer_consts(&dr, ray, map);
	ceil_addr = addr + (ray->consts->half_win_height * size_line);
	floor_addr = ceil_addr;
	ray_dirs = init_ray_dirs(ray, width, map->player);
	while (dr.y--)
	{
		i = -1;
		double row_dist = *(++dr.row_table);
		while (++i < width)
		{
			dr.ray_dirs[0] = ray_dirs[i][0];
			dr.ray_dirs[1] = ray_dirs[i][1];
			if (!init_loop_infos(&dr, row_dist, map))
			{
				tex = map->tiles[dr.tile].tex_list[5];
				color = ((int *)tex.data)[((int)(dr.real_pos[1] * tex.d_height)
						*tex.fake_size_line + ((int)(dr.real_pos[0] * tex.d_width)))];
				if (color >= 0)
					*ceil_addr = color;
				tex = map->tiles[dr.tile].tex_list[4];
				color = ((int *)tex.data)[((int)(dr.real_pos[1] * tex.d_height)
						*tex.fake_size_line + ((int)(dr.real_pos[0] * tex.d_width)))];
				if (color >= 0)
					*floor_addr = color;
			}
			ceil_addr++;
			floor_addr++;
		}
		floor_addr += width * (THREAD_COUNT - 1);
		ceil_addr -= width + size_line;
	}
	/*if (ray->cam_y >> 31)
		draw_extra_floor(floor_addr, dr, ray, map);
	else if (ray->cam_y)
		draw_extra_ceil(addr, dr, ray, map);*/
}

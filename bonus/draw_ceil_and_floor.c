/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_and_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:13:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/08 23:57:54 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	init_loop_infos(t_plane_drawer *drawer, t_map *map)
{
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

static inline void	put_plane_pixel(int *addr, int *skybox,
		t_plane_drawer *drawer, t_texture *tex)
{
	int		color;

	color = ((int *)tex->data)[((int)(drawer->real_pos[1] * tex->d_height)
			*tex->fake_size_line
			+ ((int)(drawer->real_pos[0] * tex->d_width)))];
	*addr = color;
	if (color >> 31)
		*addr = *skybox;
}

static inline void	draw_row(t_plane_drawer *drawer, int *plane_addr[4],
		t_map *map)
{
	if (!init_loop_infos(drawer, map))
	{
		put_plane_pixel(plane_addr[0], plane_addr[2],
			drawer, &map->tiles[drawer->tile].tex_list[5]);
		put_plane_pixel(plane_addr[1], plane_addr[3],
			drawer, &map->tiles[drawer->tile].tex_list[4]);
	}
	else
	{
		*plane_addr[0] = *(plane_addr[2]);
		*plane_addr[1] = *(plane_addr[3]);
	}
	drawer->floor_pos[0] += drawer->steps[0];
	drawer->floor_pos[1] += drawer->steps[1];
	plane_addr[0]++;
	plane_addr[1]++;
	plane_addr[2]++;
	plane_addr[3]++;
}

static inline void	draw_stripe(t_plane_drawer *drawer, int *plane_addr[4],
		t_map *map, int width)
{
	drawer->row_dist = *(++drawer->row_table);
	drawer->steps[0] = drawer->row_dist * map->player->ray_dir_x[1]
		* drawer->width_ratio;
	drawer->steps[1] = drawer->row_dist * map->player->ray_dir_y[1]
		* drawer->width_ratio;
	drawer->floor_pos[0] = map->player->x + drawer->row_dist
		* map->player->ray_dir_x[0];
	drawer->floor_pos[1] = map->player->y + drawer->row_dist
		* map->player->ray_dir_y[0];
	drawer->floor_pos[0] += drawer->steps[0] * drawer->start_x;
	drawer->floor_pos[1] += drawer->steps[1] * drawer->start_x;
	while (width--)
		draw_row(drawer, plane_addr, map);
}

void	draw_ceil_and_floor_tex(int *addr, t_map *map,
		t_raycast *ray, int width)
{
	t_plane_drawer	dr;
	t_player		*player;
	int				size_line;
	int				*plane_addr[4];

	size_line = ray->consts->size_line;
	plane_addr[0] = addr + (ray->consts->half_win_height * size_line);
	plane_addr[1] = plane_addr[0];
	player = map->player;
	plane_addr[2] = ray->consts->skybox_addr
		+ (ray->consts->half_win_height * size_line);
	plane_addr[2] += ray->start_x + player->skybox_scroll;
	plane_addr[3] = plane_addr[2];
	dr.width_ratio = ray->consts->width_ratio;
	dr.row_table = ray->consts->row_dist_table + ray->cam_y;
	dr.y = ray->consts->half_win_height;
	dr.start_x = ray->start_x;
	while (dr.y--)
	{
		draw_stripe(&dr, plane_addr, map, width);
		plane_addr[3] += width * (THREAD_COUNT - 1);
		plane_addr[1] += width * (THREAD_COUNT - 1);
		plane_addr[0] -= width + size_line;
		plane_addr[2] -= width + size_line;
	}
}

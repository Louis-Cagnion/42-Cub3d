/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_and_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:13:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/08/24 13:28:04 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	init_consts(t_plane_drawer *drawer,
		t_raycast *ray, int *plane_addr[4], int *size_line)
{
	*size_line = ray->consts->size_line;
	plane_addr[0] += (ray->consts->half_win_height + ray->cam_y) * *size_line;
	plane_addr[1] = plane_addr[0];
	plane_addr[2] = ray->consts->skybox_addr
		+ (ray->consts->half_win_height * *size_line);
	drawer->width_ratio = ray->consts->width_ratio;
	drawer->row_table = ray->consts->row_dist_table;
	drawer->start_x = ray->start_x;
	drawer->y = ray->consts->half_win_height - ft_abs(ray->cam_y) + 1;
}

static inline void	put_plane_pixel(int *addr,
		t_plane_drawer *drawer, t_texture *tex)
{
	int		color;

	color = ((int *)tex->data)[((int)(drawer->real_pos[1] * tex->d_height)
			*tex->fake_size_line
			+ ((int)(drawer->real_pos[0] * tex->d_width)))];
	if (!(color >> 31))
		*addr = color;
}

static inline void	draw_row(t_plane_drawer *drawer, int *plane_addr[4],
		t_map *map)
{
	*plane_addr[0] = *plane_addr[2];
	*plane_addr[1] = *plane_addr[3];
	drawer->map_pos[1] = (int)drawer->floor_pos[1];
	drawer->map_pos[0] = (int)drawer->floor_pos[0];
	if (!(drawer->map_pos[1] >= map->h_map || drawer->map_pos[0] >= map->w_map
			|| drawer->floor_pos[1] < 0 || drawer->floor_pos[0] < 0))
	{
		drawer->tile = map->map_array[drawer->map_pos[1]][drawer->map_pos[0]];
		drawer->real_pos[0] = drawer->floor_pos[0] - drawer->map_pos[0];
		drawer->real_pos[1] = drawer->floor_pos[1] - drawer->map_pos[1];
		put_plane_pixel(plane_addr[0],
			drawer, &map->tiles[drawer->tile].tex_list[5]);
		put_plane_pixel(plane_addr[1],
			drawer, &map->tiles[drawer->tile].tex_list[4]);
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
	double	row_dist_ratio;

	drawer->row_dist = *(++drawer->row_table);
	row_dist_ratio = drawer->row_dist * drawer->width_ratio;
	drawer->steps[0] = row_dist_ratio * map->player->ray_dir_x[1];
	drawer->steps[1] = row_dist_ratio * map->player->ray_dir_y[1];
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
	int				size_line;
	int				*plane_addr[4];

	plane_addr[0] = addr;
	init_consts(&dr, ray, plane_addr, &size_line);
	plane_addr[2] += ray->start_x + map->player->skybox_scroll;
	plane_addr[3] = plane_addr[2];
	while (dr.y--)
	{
		draw_stripe(&dr, plane_addr, map, width);
		plane_addr[3] = (plane_addr[3] - width) + size_line;
		plane_addr[1] = (plane_addr[1] - width) + size_line;
		plane_addr[0] -= width + size_line;
		plane_addr[2] -= width + size_line;
	}
	if (ray->cam_y >> 31)
		draw_extra_floor(&dr, ray, map, plane_addr);
	else if (ray->cam_y)
		draw_extra_ceil(&dr, ray, map, plane_addr);
}

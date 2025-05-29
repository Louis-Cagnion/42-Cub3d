/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_and_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:13:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/29 18:58:45 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	get_tex_pixel(t_texture tex, int x, int y)
{
	return (*(int *)(tex.data + (y * tex.size_line + (x << 2))));
}

static inline void	draw_ceil_and_floor(int *floor, int *ceil,
		double inter_dist[3], t_map map)
{
	t_texture	texture;
	double		floor_x;
	double		floor_y;

	floor_x = map.player->x + inter_dist[2] * inter_dist[0];
	floor_y = map.player->y + inter_dist[2] * inter_dist[1];
	floor_x -= (int)floor_x;
	floor_y -= (int)floor_y;
	texture = map.tex_list[4];
	*floor = get_tex_pixel(texture,
			floor_x * texture.width,
			floor_y * texture.height
			);
	texture = map.tex_list[5];
	*ceil = get_tex_pixel(texture,
			floor_x * texture.width,
			floor_y * texture.height
			);
}

void	draw_ceil_and_floor_tex(int *addr, int size_line,
		t_map map, t_raycast *ray)
{
	int		y;
	int		*floor_addr;
	int		*ceil_addr;
	double	inter_dist[3];
	int		p;

	ceil_addr = addr + (ray->wall_pos[1] * size_line);
	floor_addr = addr + (ray->wall_pos[0] * size_line);
	p = ray->half_win_height - ray->wall_pos[0] + ray->cam_y;
	inter_dist[0] = map.player->ray_dir_x[0]
		+ ray->cam_x * map.player->ray_dir_x[1];
	inter_dist[1] = map.player->ray_dir_y[0]
		+ ray->cam_x * map.player->ray_dir_y[1];
	y = ft_min(ray->wall_pos[0], WIN_HEIGHT - ray->wall_pos[1]);
	while (y--)
	{
		inter_dist[2] = ray->row_dist_table[p++];
		draw_ceil_and_floor(ceil_addr, floor_addr, inter_dist, map);
		floor_addr -= size_line;
		ceil_addr += size_line;
	}
	if (ray->cam_y >> 31)
		draw_extra_floor(ceil_addr, inter_dist, ray, map);
	else if (ray->cam_y)
		draw_extra_ceil(addr, inter_dist, ray, map);
}

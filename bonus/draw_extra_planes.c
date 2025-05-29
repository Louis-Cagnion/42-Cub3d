/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_extra_planes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:18:09 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/29 15:22:02 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	get_tex_pixel(t_texture tex, int x, int y)
{
	return (*(int *)(tex.data + (y * tex.size_line + (x << 2))));
}

static inline void	draw_vert_tex(int *addr, double inter_dist[3],
		t_map map, int i)
{
	t_texture	texture;
	double		floor_x;
	double		floor_y;

	floor_x = map.player->x + inter_dist[2] * inter_dist[0];
	floor_y = map.player->y + inter_dist[2] * inter_dist[1];
	floor_x -= (int)floor_x;
	floor_y -= (int)floor_y;
	texture = map.tex_list[i];
	*addr = get_tex_pixel(texture,
			floor_x * texture.width,
			floor_y * texture.height
			);
}

void	draw_extra_floor(int *addr, double inter_dist[3],
		t_raycast *ray, t_map map)
{
	double	*dist_table;
	int		p;
	int		size_line;
	int		height;

	height = WIN_HEIGHT - (ray->wall_pos[1] + ray->wall_pos[0]);
	size_line = ray->size_line;
	p = ray->half_win_height - ray->cam_y - height;
	dist_table = ray->row_dist_table;
	while (height--)
	{
		inter_dist[2] = dist_table[p++];
		draw_vert_tex(addr, inter_dist, map, 4);
		addr += size_line;
	}
}

void	draw_extra_ceil(int *addr, double inter_dist[3],
		t_raycast *ray, t_map map)
{
	double	*dist_table;
	int		p;
	int		size_line;
	int		height;

	height = ray->wall_pos[0] - (WIN_HEIGHT - ray->wall_pos[1]) + 1;
	height++;
	size_line = ray->size_line;
	p = ray->half_win_height + ray->cam_y;
	dist_table = ray->row_dist_table;
	while (height--)
	{
		inter_dist[2] = dist_table[p--];
		draw_vert_tex(addr, inter_dist, map, 5);
		addr += size_line;
	}
}

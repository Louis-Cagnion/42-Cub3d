/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:17:03 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/09 18:17:33 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	get_tex_pixel(t_texture tex, int x, int y)
{
	return (*(int *)(tex.data + (y * tex.size_line + (x << 2))));
}

static inline void	draw_ceil_and_floor(int *floor, int *ceil,
			double inter_dists[3], t_map map)
{
	t_texture	texture;
	double		floor_x;
	double		floor_y;
	int			color;

	floor_x = map.player->x + inter_dists[2] * inter_dists[0];
	floor_y = map.player->y + inter_dists[2] * inter_dists[1];
	floor_x -= (int)floor_x;
	floor_y -= (int)floor_y;
	if (floor_y < 0 || floor_x < 0)
		return ;
	texture = map.tex_list[5];
	color = get_tex_pixel(texture,
			floor_x * texture.width,
			floor_y * texture.height
			);
	*floor = color;
	texture = map.tex_list[4];
	color = get_tex_pixel(texture,
			floor_x * texture.width,
			floor_y * texture.height
			);
	*ceil = color;
}

static inline void	draw_ceil_and_floor_tex(int **addr, int size_line,
		t_map map, t_raycast *ray)
{
	int		y;
	int		*floor_addr;
	int		*ceil_addr;
	double	inter_dist[3];
	int		p;

	floor_addr = *addr + (ray->wall_pos[0] * size_line);
	ceil_addr = *addr + (ray->wall_pos[1] * size_line);
	*addr = floor_addr;
	p = ray->wall_pos[1] - ray->half_win_height;
	inter_dist[0] = map.player->ray_dir_x[0]
		+ (ray->cam_x * map.player->ray_dir_x[1]);
	inter_dist[1] = map.player->ray_dir_y[0]
		+ (ray->cam_x * map.player->ray_dir_y[1]);
	y = ray->wall_pos[0];
	while (y--)
	{
		inter_dist[2] = ray->row_dist_table[p++];
		draw_ceil_and_floor(floor_addr, ceil_addr, inter_dist, map);
		floor_addr -= size_line;
		ceil_addr += size_line;
	}
}

static inline void	draw_column(t_game *game, int x, t_map map_infos,
		t_raycast *ray_infos)
{
	t_img	*img;
	int		*addr;
	int		size_line;

	img = game->mlx.img;
	size_line = ray_infos->size_line;
	addr = (int *)(img->data + (x * ray_infos->fake_bpp));
	draw_ceil_and_floor_tex(&addr, size_line,
		map_infos, ray_infos);
	put_texture(game, addr, ray_infos, size_line);
}

void	display_screen(t_game *game, t_opti_const consts,
		t_mlx mlx, t_raycast infos)
{
	double		cam_coef;
	int			x;

	x = WIN_WIDTH;
	cam_coef = consts.cam_coef;
	while (x)
	{
		infos.wall_dist = get_wall_dist(game->player, &infos,
				cam_coef * x - 1, game->map.map_array);
		infos.z_buffer[x - 1] = infos.wall_dist;
		infos.line_height = WIN_HEIGHT / infos.wall_dist;
		infos.half_line_height = infos.line_height >> 1;
		infos.wall_pos[0] = consts.half_height - infos.half_line_height;
		if (infos.wall_pos[0] >> 31)
			infos.wall_pos[0] = 0;
		infos.wall_pos[1] = infos.half_line_height + consts.half_height;
		if (infos.wall_pos[1] > WIN_HEIGHT)
			infos.wall_pos[1] = WIN_HEIGHT;
		draw_column(game, x--, game->map, &infos);
		infos.cam_x -= infos.cam_x_step;
	}
	draw_sprites(infos, game);
	mlx_put_image_to_window(mlx.init,
		mlx.window, mlx.img, 0, 0);
}

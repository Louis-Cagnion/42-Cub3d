/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:17:03 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:42 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	draw_column(t_game *game, int x, t_map map_infos,
		t_raycast *infos)
{
	t_img	*img;
	int		*addr;
	int		size_line;

	img = game->mlx.img;
	size_line = infos->size_line;
	addr = (int *)(img->data + (x * infos->fake_bpp));
	draw_ceil_and_floor_tex(addr, size_line,
		map_infos, infos);
	addr += size_line * infos->wall_pos[0];
	put_texture(game, addr, infos, size_line);
}

void	display_screen(t_game *game, t_opti_const consts, t_raycast infos)
{
	double		cam_coef;
	int			x;

	x = WIN_WIDTH;
	cam_coef = consts.cam_coef;
	while (x)
	{
		infos.wall_dist = get_wall_dist(game->player, &infos,
				cam_coef * x - 1, game->map);
		infos.z_buffer[x - 1] = infos.wall_dist;
		infos.line_height = WIN_HEIGHT / infos.wall_dist;
		infos.half_line_height = infos.line_height >> 1;
		infos.wall_pos[0] = consts.half_height - infos.half_line_height
			+ infos.cam_y;
		infos.wall_pos[1] = consts.half_height + infos.half_line_height
			+ infos.cam_y;
		if (infos.wall_pos[0] >> 31)
			infos.wall_pos[0] = 0;
		if (infos.wall_pos[1] > WIN_HEIGHT)
			infos.wall_pos[1] = WIN_HEIGHT;
		draw_column(game, x--, game->map, &infos);
		infos.cam_x -= infos.cam_x_step;
	}
	draw_sprites(infos, game);
}

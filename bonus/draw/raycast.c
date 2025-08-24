/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:17:03 by gakarbou          #+#    #+#             */
/*   Updated: 2025/08/24 18:09:18 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	draw_column(t_game *game, t_raycast *infos)
{
	int		*addr;
	int		size_line;

	size_line = infos->consts->size_line;
	addr = infos->addr++;
	put_texture(game, addr, infos, size_line);
}

static void	cast_rays(t_game *game, t_raycast *infos, int x, int width)
{
	int		*addr;

	addr = (int *)infos->addr;
	while (width--)
	{
		infos->cast_infos[x] = cast_ray(init_ray_consts(&game->player,
					infos->consts->cam_coef * x - 1),
				game, addr, -1);
		addr++;
		x++;
	}
}

void	display_screen(t_game *game, t_raycast infos, int x, int width)
{
	draw_ceil_and_floor_tex(infos.addr, &game->map, &infos, width);
	cast_rays(game, &infos, x, width);
	return ;
	infos.cast_infos = infos.cast_infos + x;
	while (width--)
	{
		infos.wall_dist = infos.cast_infos->wall_dist;
		if (infos.wall_dist < 0)
		{
			infos.cast_infos++;
			continue ;
		}
		infos.line_height = WIN_HEIGHT / infos.wall_dist;
		infos.half_line_height = infos.line_height >> 1;
		infos.wall_pos[0] = infos.consts->half_win_height
			- infos.half_line_height + infos.cam_y;
		infos.wall_pos[1] = infos.wall_pos[0] + (infos.half_line_height << 1);
		if (infos.wall_pos[0] >> 31)
			infos.wall_pos[0] = 0;
		if (infos.wall_pos[1] > WIN_HEIGHT)
			infos.wall_pos[1] = WIN_HEIGHT;
		draw_column(game, &infos);
		infos.cast_infos++;
	}
}

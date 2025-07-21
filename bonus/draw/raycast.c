/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:17:03 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/21 18:08:07 by gakarbou         ###   ########.fr       */
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
	while (width--)
	{
		infos->cast_infos[x].wall_dist = get_wall_dist(game->player,
				&infos->cast_infos[x], infos->consts->cam_coef * x - 1,
				&game->map);
		x++;
	}
}

void	display_screen(t_game *game, t_raycast infos, int x, int width)
{
	cast_rays(game, &infos, x, width);
	infos.cast_infos = infos.cast_infos + x;
	draw_ceil_and_floor_tex(infos.addr, &game->map, &infos, width);
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
		infos.wall_pos[1] = infos.wall_pos[0] + infos.line_height;
		if (infos.wall_pos[0] >> 31)
			infos.wall_pos[0] = 0;
		if (infos.wall_pos[1] > WIN_HEIGHT)
			infos.wall_pos[1] = WIN_HEIGHT;
		draw_column(game, &infos);
		infos.cast_infos++;
	}
}

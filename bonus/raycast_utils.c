/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:23:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/09 20:08:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	*init_row_dist_table(int half_height)
{
	double	*table;
	int		i;

	table = malloc(sizeof(double) * WIN_HEIGHT);
	if (!table)
	{
		ft_error("Memory error\n");
		exit(0);
	}
	table[0] = 1e10;
	i = 0;
	while (++i < WIN_HEIGHT)
		table[i] = half_height / (double)i;
	return (table);
}

void	init_raycast(t_game *game, t_raycast *raycast)
{
	game->consts.float_width = (double)WIN_WIDTH;
	game->consts.half_height = WIN_HEIGHT / 2;
	game->consts.half_width = WIN_WIDTH / 2;
	game->raycast.cam_coef = 2 / game->consts.float_width;
	raycast->half_win_height = game->consts.half_height;
	raycast->cam_x = 1;
	raycast->cam_x_step = (double)1 / WIN_WIDTH;
	raycast->row_dist_table
		= init_row_dist_table(raycast->half_win_height);
	game->map.player = &game->player;
	game->player.half_win_height = game->consts.half_height;
	raycast->z_buffer = malloc(sizeof(double) * WIN_WIDTH);
	raycast->size_line = game->mlx.img->size_line >> 2;
	raycast->fake_bpp = game->mlx.img->bpp >> 3;
	raycast->tex_fake_bpp = raycast->fake_bpp >> 2;
}

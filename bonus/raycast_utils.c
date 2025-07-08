/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:23:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/07 21:31:54 by gakarbou         ###   ########.fr       */
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

static t_opti_const	*compute_const(t_game *game)
{
	t_opti_const	*dest;

	dest = malloc(sizeof(t_opti_const));
	dest->float_width = (double)WIN_WIDTH;
	dest->float_height = (double)WIN_HEIGHT;
	dest->half_win_width = WIN_WIDTH / 2;
	dest->half_win_height = WIN_HEIGHT / 2;
	dest->skybox = create_skybox("assets/sky.xpm", game->mlx.init);
	dest->skybox_addr = (int *)dest->skybox.data;
	dest->size_line = game->mlx.img->size_line >> 2;
	dest->fake_bpp = game->mlx.img->bpp >> 3;
	dest->tex_fake_bpp = dest->fake_bpp >> 2;
	dest->row_dist_table
		= init_row_dist_table(dest->half_win_height);
	dest->cam_x_step = (double)1 / WIN_WIDTH;
	dest->cam_coef = 2 / dest->float_width;
	game->player.half_win_height = dest->half_win_height;
	return (dest);
}

void	init_raycast(t_game *game, t_raycast *raycast)
{
	raycast->cam_x = 1;
	game->map.player = &game->player;
	raycast->z_buffer = malloc(sizeof(double) * WIN_WIDTH);
	raycast->consts = compute_const(game);
	raycast->img = game->mlx.img;
	raycast->addr = (int *)raycast->img->data;
}

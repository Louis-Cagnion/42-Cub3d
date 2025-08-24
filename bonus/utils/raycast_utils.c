/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:23:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/31 11:51:46 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	init_steps_infos(t_player *player, double ray_dir[2],
		double side_dist[2], int steps[2])
{
	steps[0] = -1;
	side_dist[0] = player->x_mantissa;
	if (ray_dir[0] >= 0)
	{
		steps[0] = 1;
		side_dist[0] = 1 - side_dist[0];
	}
	steps[1] = -1;
	side_dist[1] = player->y_mantissa;
	if (ray_dir[1] >= 0)
	{
		steps[1] = 1;
		side_dist[1] = 1 - side_dist[1];
	}
}

t_wall_drawer	init_ray_consts(t_player *player, double cam_x)
{
	t_wall_drawer	drawer;

	drawer.ray_dir[0] = player->direction_x + player->plane_x * cam_x;
	drawer.ray_dir[1] = player->direction_y + player->plane_y * cam_x;
	drawer.map_pos[0] = player->int_x;
	drawer.map_pos[1] = player->int_y;
	drawer.delta_dist[0] = 1000;
	if (drawer.ray_dir[0])
		drawer.delta_dist[0] = fabs(1 / drawer.ray_dir[0]);
	drawer.delta_dist[1] = 1000;
	if (drawer.ray_dir[1])
		drawer.delta_dist[1] = fabs(1 / drawer.ray_dir[1]);
	init_steps_infos(player, drawer.ray_dir, drawer.side_dist, drawer.steps);
	drawer.side_dist[0] *= drawer.delta_dist[0];
	drawer.side_dist[1] *= drawer.delta_dist[1];
	drawer.side = 0;
	return (drawer);
}

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
	dest->size_line = game->mlx.img->size_line >> 2;
	dest->skybox = create_skybox("assets/sky.xpm", game->mlx.init);
	dest->skybox_addr = (int *)(dest->skybox.data
			+ (dest->half_win_height * dest->size_line * 4));
	dest->fake_bpp = game->mlx.img->bpp >> 3;
	dest->tex_fake_bpp = dest->fake_bpp >> 2;
	dest->row_dist_table
		= init_row_dist_table(dest->half_win_height);
	dest->width_ratio = (double)1 / WIN_WIDTH;
	dest->height_ratio = (double)1 / WIN_HEIGHT;
	dest->cam_coef = 2 / dest->float_width;
	game->player.half_win_height = dest->half_win_height;
	return (dest);
}

void	init_raycast(t_game *game, t_raycast *raycast)
{
	game->map.player = &game->player;
	raycast->cast_infos = malloc(sizeof(t_cast_infos) * WIN_WIDTH);
	raycast->consts = compute_const(game);
	game->consts = raycast->consts;
	raycast->width = WIN_WIDTH / THREAD_COUNT;
	raycast->img = game->mlx.img;
	raycast->addr = (int *)raycast->img->data;
}

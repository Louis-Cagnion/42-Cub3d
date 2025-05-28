/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:51:28 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/28 22:44:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	quit(t_game *game)
{
	mlx_loop_end(game->mlx.init);
	return (0);
}

static int	pressed_key(int key, t_game *game)
{
	if (key == XK_Escape)
		quit(game);
	else if (key == 'w')
		game->key_infos.w_key = 1;
	else if (key == 'a')
		game->key_infos.a_key = 1;
	else if (key == 's')
		game->key_infos.s_key = 1;
	else if (key == 'd')
		game->key_infos.d_key = 1;
	else if (key == XK_Left)
		game->key_infos.left_key = 1;
	else if (key == XK_Right)
		game->key_infos.right_key = 1;
	return (0);
}

static int	release_key(int key, t_game *game)
{
	if (key == 'w')
		game->key_infos.w_key = 0;
	else if (key == 'a')
		game->key_infos.a_key = 0;
	else if (key == 's')
		game->key_infos.s_key = 0;
	else if (key == 'd')
		game->key_infos.d_key = 0;
	else if (key == XK_Left)
		game->key_infos.left_key = 0;
	else if (key == XK_Right)
		game->key_infos.right_key = 0;
	return (0);
}

static int	loop(t_game *game)
{
	key_pressed_check_controls(game);
	key_pressed_check_camera(&game->player, game->key_infos);
	display_screen(game, game->consts, game->mlx, game->raycast);
	put_minimap_pixels(game, game->map.minimap);
	return (0);
}

void	init_hooks(t_game *game)
{
	game->consts.float_width = (double)WIN_WIDTH;
	game->consts.half_height = WIN_HEIGHT / 2;
	game->consts.cam_coef = 2 / game->consts.float_width;
	game->raycast.half_win_height = game->consts.half_height;
	game->raycast.cam_x = 1;
	game->raycast.cam_x_step = (double)1 / WIN_WIDTH;
	game->raycast.row_dist_table
		= init_row_dist_table(game->raycast.half_win_height);
	game->map.player = &game->player;
	init_minimap(game);
	mlx_hook(game->mlx.window, DestroyNotify, KeyReleaseMask, quit, game);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask, pressed_key, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask, release_key, game);
	mlx_loop_hook(game->mlx.init, loop, game);
}

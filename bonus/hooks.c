/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:51:28 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/28 17:00:39 by gakarbou         ###   ########.fr       */
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
	key_pressed_check_controls(game, &game->player);
	key_pressed_check_camera(&game->player, game->key_infos);
	update_entities(game->map.entity_list, game->player, game->consts);
	display_screen(game, game->consts, game->mlx, game->raycast);
	return (0);
}

void	init_hooks(t_game *game)
{
	game->consts.float_width = (double)WIN_WIDTH;
	game->consts.half_height = WIN_HEIGHT / 2;
	game->consts.half_width = WIN_WIDTH / 2;
	game->consts.cam_coef = 2 / game->consts.float_width;
	game->raycast.half_win_height = game->consts.half_height;
	game->raycast.cam_x = 1;
	game->raycast.cam_x_step = (double)1 / WIN_WIDTH;
	game->raycast.row_dist_table
		= init_row_dist_table(game->raycast.half_win_height);
	game->map.player = &game->player;
	game->raycast.z_buffer = malloc(sizeof(double) * WIN_WIDTH);
	game->raycast.size_line = game->mlx.img->size_line >> 2;
	game->raycast.fake_bpp = game->mlx.img->bpp >> 3;
	game->raycast.tex_fake_bpp = game->raycast.fake_bpp >> 2;
	game->map.entity_list = create_cell(
			create_entity("./assets/mario.xpm", 2.5, 3.8, game->mlx.init));
	mlx_hook(game->mlx.window, DestroyNotify, KeyReleaseMask, quit, game);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask, pressed_key, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask, release_key, game);
	mlx_loop_hook(game->mlx.init, loop, game);
}

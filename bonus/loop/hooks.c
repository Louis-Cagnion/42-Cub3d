/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:51:28 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/12 21:24:53 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	quit(t_game *game)
{
	int		i;

	pthread_mutex_lock(&game->mutex);
	game->stop = 1;
	pthread_mutex_unlock(&game->mutex);
	i = -1;
	while (++i < THREAD_COUNT)
		pthread_join(game->thread[i].thread, NULL);
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
	else if (key == XK_Up)
		game->key_infos.up_key = 1;
	else if (key == XK_Down)
		game->key_infos.down_key = 1;
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
	else if (key == XK_Up)
		game->key_infos.up_key = 0;
	else if (key == XK_Down)
		game->key_infos.down_key = 0;
	return (0);
}

void	init_hooks(t_game *game)
{
	int		i;

	i = -1;
	game->map.entity_list = create_cell(
			create_entity("./assets/snas.xpm", 2.5, 3.8, game->mlx.init));
	init_raycast(game, &game->raycast);
	init_minimap(&game->map.minimap, game->map, game->mlx);
	game->thread = malloc(sizeof(t_thread_info) * THREAD_COUNT);
	key_pressed_check_controls(game, &game->player);
	key_pressed_check_camera(&game->player, game->key_infos);
	pthread_mutex_init(&game->mutex, NULL);
	while (++i < THREAD_COUNT)
	{
		game->thread[i].index = i;
		game->thread[i].is_finished = 0;
		game->thread[i].raycast = game->raycast;
		game->thread[i].game = game;
		pthread_create(&game->thread[i].thread, NULL,
			thread_routine, &game->thread[i]);
	}
	mlx_hook(game->mlx.window, DestroyNotify, KeyReleaseMask, quit, game);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask, pressed_key, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask, release_key, game);
	mlx_loop_hook(game->mlx.init, loop, game);
}

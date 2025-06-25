/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:51:28 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/25 17:50:32 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	quit(t_game *game)
{
	mlx_loop_end(game->mlx.init);
	return (0);
}

static int	thread_finished(t_game *game)
{
	int				res;
	int				i;
	t_thread_info	thread;

	res = 1;
	i = -1;
	while (++i < THREAD_COUNT)
	{
		thread = game->thread[i];
		pthread_mutex_lock(&game->jsp);
		if (!thread.is_finished)
			res = 0;
		pthread_mutex_unlock(&game->jsp);
		if (!res)
			return (0);
	}
	return (1);
}

static void	reset_all(t_game *game)
{
	int		i;

	i = -1;
	while (++i < THREAD_COUNT)
		game->thread[i].is_finished = 0;
}

static void	thread_draw_screen(t_game *game)
{
	pthread_mutex_lock(&game->jsp);
	game->next_draw = THREAD_COUNT;
	game->thread_wait = 0;
	pthread_mutex_unlock(&game->jsp);
	while (!thread_finished(game))
		usleep(1);
	mlx_put_image_to_window(game->mlx.init,
		game->mlx.window, game->mlx.img, 0, 0);
	pthread_mutex_lock(&game->jsp);
	reset_all(game);
	pthread_mutex_unlock(&game->jsp);
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

static int	loop(t_game *game)
{
	int			ret_cam;
	int			ret_mov;

	game->raycast.cam_y = game->player.cam_y;
	ret_mov = key_pressed_check_controls(game, &game->player);
	ret_cam = key_pressed_check_camera(&game->player, game->key_infos);
	thread_draw_screen(game);
	/*draw_sprites(game->raycast, game);
	update_entities(game->map.entity_list, game->player, game->consts);
	game->map.entity_list = create_cell(
			create_entity("./assets/snas.xpm", 2.5, 3.8, game->mlx.init));
	update_entities(game->map.entity_list, game->player, game->consts);*/
	return (0);
}

void	init_hooks(t_game *game)
{
	int		i;

	game->stop = 0;
	i = -1;
	init_raycast(game, &game->raycast);
	key_pressed_check_controls(game, &game->player);
	key_pressed_check_camera(&game->player, game->key_infos);
	pthread_mutex_init(&game->jsp, NULL);
	game->thread_wait = 0;
	game->next_draw = 0;
	while (++i < THREAD_COUNT)
	{
		game->thread[i].index = i;
		game->thread[i].is_finished = 0;
		game->thread[i].raycast = game->raycast;
		game->thread[i].game = game;
		pthread_create(&game->thread[i].thread, NULL,
				thread_routine, &game->thread[i]);
	}
	thread_draw_screen(game);
	mlx_hook(game->mlx.window, DestroyNotify, KeyReleaseMask, quit, game);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask, pressed_key, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask, release_key, game);
	mlx_loop_hook(game->mlx.init, loop, game);
}

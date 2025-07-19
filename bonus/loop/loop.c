/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:31:25 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/19 22:07:16 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	thread_finished(t_game *game)
{
	int				res;
	int				i;
	t_thread_info	thread;

	res = 1;
	i = -1;
	while (++i < THREAD_COUNT)
	{
		pthread_mutex_lock(&game->mutex);
		thread = game->thread[i];
		if (!thread.is_finished)
			res = 0;
		if (game->stop)
		{
			pthread_mutex_unlock(&game->mutex);
			return (1);
		}
		pthread_mutex_unlock(&game->mutex);
		if (!res)
			return (0);
	}
	return (1);
}

static inline void	reset_all(t_game *game)
{
	int			i;

	i = -1;
	while (++i < THREAD_COUNT)
	{
		game->thread[i].is_finished = 0;
		game->thread[i].sprite.entity = NULL;
	}
}

static inline void	thread_draw_screen(t_game *game)
{
	pthread_mutex_lock(&game->mutex);
	reset_all(game);
	game->next_draw = THREAD_COUNT;
	pthread_mutex_unlock(&game->mutex);
	while (!thread_finished(game))
		usleep(1);
	command_thread_sprites(game);
	mlx_put_image_to_window(game->mlx.init, game->mlx.window,
		game->mlx.img, 0, 0);
	put_minimap(game->mlx, game->map.minimap, game->player);
}

int	loop(t_game *game)
{
	game->raycast.cam_y = game->player.cam_y;
	key_pressed_check_controls(game, &game->player);
	key_pressed_check_camera(&game->player, game->key_infos);
	update_entities(game->map.entity_list, game->player, game->raycast.consts);
	thread_draw_screen(game);
	return (0);
}

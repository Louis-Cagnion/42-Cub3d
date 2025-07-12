/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_draw_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:12:52 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/12 19:13:14 by gakarbou         ###   ########.fr       */
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

static inline void	thread_draw_sprite(t_game *game)
{
	int			i;

	i = -1;
	pthread_mutex_lock(&game->mutex);
	while (++i < THREAD_COUNT)
		game->thread[i].is_finished = 0;
	game->next_draw = THREAD_COUNT;
	pthread_mutex_unlock(&game->mutex);
	while (!thread_finished(game))
		usleep(1);
}

void	command_thread_sprites(t_game *game)
{
	t_list		*entities;
	t_entity	*entity;
	int			i;
	int			sprite_part;

	entities = game->map.entity_list;
	while (entities)
	{
		entity = (t_entity *)entities->data;
		entities = entities->next;
		if (entity->draw_dir_y <= 0 || entity->screen_width >> 31
			|| entity->player_dist < 0.1)
			continue ;
		i = -1;
		sprite_part = entity->screen_width / THREAD_COUNT;
		pthread_mutex_lock(&game->mutex);
		while (++i < THREAD_COUNT)
		{
			game->thread[i].sprite.entity = entity;
			game->thread[i].sprite.start = sprite_part * i;
			game->thread[i].sprite.width = sprite_part;
		}
		pthread_mutex_unlock(&game->mutex);
		thread_draw_sprite(game);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:11:57 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/08 22:40:00 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	thread_finished(t_game *game, t_thread_info *thread)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&game->jsp);
	if (game->stop)
		res++;
	else if (thread->is_finished)
	{
		pthread_mutex_unlock(&game->jsp);
		return (0);
	}
	else if (game->next_draw)
	{
		res++;
		game->next_draw--;
	}
	pthread_mutex_unlock(&game->jsp);
	return (res);
}

static inline int	check_end(t_game *game)
{
	int		res;

	res = 0;
	pthread_mutex_lock(&game->jsp);
	if (game->stop)
		res++;
	pthread_mutex_unlock(&game->jsp);
	return (res);
}

void	*thread_routine(void *ptr)
{
	t_game			*game;
	t_thread_info	*thread;

	thread = (t_thread_info *)ptr;
	game = thread->game;
	thread->width = WIN_WIDTH / THREAD_COUNT;
	thread->start = thread->index * thread->width;
	thread->raycast.addr += thread->start;
	thread->raycast.start_x = thread->start;
	while (!check_end(game))
	{
		while (!thread_finished(game, thread))
			usleep(1);
		if (check_end(game))
			break ;
		thread->raycast.cam_y = game->player.cam_y;
		display_screen(game, thread->raycast, thread->start, thread->width);
		pthread_mutex_lock(&game->jsp);
		thread->is_finished = 1;
		pthread_mutex_unlock(&game->jsp);
	}
	return (NULL);
}

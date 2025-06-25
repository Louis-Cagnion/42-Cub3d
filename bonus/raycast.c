/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:17:03 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/25 17:34:19 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	draw_column(t_game *game, int x, t_map map_infos,
		t_raycast *infos)
{
	t_img	*img;
	int		*addr;
	int		size_line;

	img = game->mlx.img;
	size_line = infos->size_line;
	addr = (int *)(img->data + (x * infos->fake_bpp));
	draw_ceil_and_floor_tex(addr, size_line,
		map_infos, infos);
	addr += size_line * infos->wall_pos[0];
	put_texture(game, addr, infos, size_line);
}

void	display_screen(t_game *game, t_raycast infos, int x, int width)
{
	double		cam_coef;

	cam_coef = infos.cam_coef;
	infos.cam_x = (infos.cam_x_step * x);
	while (x < width)
	{
		infos.wall_dist = get_wall_dist(game->player, &infos,
				cam_coef * x - 1, game->map);
		infos.z_buffer[x] = infos.wall_dist;
		infos.line_height = WIN_HEIGHT / infos.wall_dist;
		infos.line_height -= infos.line_height % 2;
		infos.half_line_height = infos.line_height >> 1;
		infos.wall_pos[0] = infos.half_win_height - infos.half_line_height
			+ infos.cam_y;
		infos.wall_pos[1] = infos.half_win_height + infos.half_line_height
			+ infos.cam_y;
		if (infos.wall_pos[0] >> 31)
			infos.wall_pos[0] = 0;
		if (infos.wall_pos[1] > WIN_HEIGHT)
			infos.wall_pos[1] = WIN_HEIGHT;
		draw_column(game, x++, game->map, &infos);
		infos.cam_x += infos.cam_x_step;
	}
}

static int	thread_finished(t_game *game, t_thread_info *thread)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&game->jsp);
	if (thread->is_finished)
	{
		pthread_mutex_unlock(&game->jsp);
		return (0);
	}
	if (game->next_draw)
	{
		res++;
		game->next_draw--;
	}
	pthread_mutex_unlock(&game->jsp);
	return (res);
}

void	*thread_routine(void *ptr)
{
	t_game			*game;
	t_thread_info	*thread;

	thread = (t_thread_info *)ptr;
	game = thread->game;
	thread->start = thread->index * (WIN_WIDTH / THREAD_COUNT);
	thread->width = thread->start + (WIN_WIDTH / THREAD_COUNT);
	while (!game->stop)
	{
		while (!thread_finished(game, thread))
			usleep(1);
		thread->raycast.cam_y = game->player.cam_y;
		display_screen(game, thread->raycast, thread->start, thread->width);
		pthread_mutex_lock(&game->jsp);
		thread->is_finished = 1;
		pthread_mutex_unlock(&game->jsp);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:17:03 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/08 13:42:37 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	draw_column(t_game *game, t_map *map_infos,
		t_raycast *infos)
{
	int		*addr;
	int		size_line;

	size_line = infos->consts->size_line;
	addr = infos->addr++;
	put_texture(game, addr, infos, size_line);
}

/*
static void reset_background(int *addr, int width, t_raycast *infos, t_player *player)
{
	int	screen_pos[2];
    int scroll = (int)(((atan2(player->direction_y, player->direction_x) + M_PI) / (2 * M_PI)) * WIN_WIDTH) % WIN_WIDTH;
	int	*skybox = infos->consts->skybox_addr;

	screen_pos[1] = -1;
	skybox += scroll + infos->start_x;
	while (++screen_pos[1] < WIN_HEIGHT)
    {
		screen_pos[0] = -1;
		while (++screen_pos[0] < width)
            *(addr++) = *(skybox++);
		addr += width * (THREAD_COUNT - 1);
		skybox += width * (THREAD_COUNT - 1);
    }
}
*/

static void	reset_background(int *addr, int width, t_raycast *ray, t_map *map)
{
	draw_ceil_and_floor_tex(addr++, ray->consts->size_line, map, ray, width);
}

void	display_screen(t_game *game, t_raycast infos, int x, int width)
{
	infos.cam_x = (infos.consts->cam_x_step * x);
	reset_background(infos.addr, width, &infos, &game->map);
	while (width--)
	{
		infos.wall_dist = get_wall_dist(game->player, &infos,
				infos.consts->cam_coef * x++ - 1, &game->map);
		infos.z_buffer[x] = infos.wall_dist;
		infos.line_height = WIN_HEIGHT / infos.wall_dist;
		infos.half_line_height = infos.line_height >> 1;
		infos.wall_pos[0] = infos.consts->half_win_height - infos.half_line_height
			+ infos.cam_y;
		infos.wall_pos[1] = infos.wall_pos[0] + (infos.half_line_height << 1);
		if (infos.wall_pos[0] >> 31)
			infos.wall_pos[0] = 0;
		if (infos.wall_pos[1] > WIN_HEIGHT)
			infos.wall_pos[1] = WIN_HEIGHT;
		draw_column(game, &game->map, &infos);
		infos.cam_x += infos.consts->cam_x_step;
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
	thread->width = WIN_WIDTH / THREAD_COUNT;
	thread->start = thread->index * thread->width;
	thread->raycast.addr += thread->start;
	thread->raycast.start_x = thread->start;
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

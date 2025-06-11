/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/11 20:04:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline char	return_token_map(t_map map, t_minimap mini, int y, int x)
{
	int	line;
	int	col;

	line = (int)((y - mini.start_y) / mini.ratio_y);
	if (line == map.h_map)
		return ('1');
	if (line > map.h_map)
		return ('0');
	col = (int)((x - mini.start_x) / mini.ratio_x);
	if (col > map.w_map)
		return ('0');
	if (line == map.w_map)
		return ('1');
	return (map.map_array[line][col]);
}

static inline void	put_player_minimap(t_mlx mlx, double x, double y, t_minimap mini)
{
	int	x_backup;
	int	x_player;
	int	y_player;
	int	limit_x;
	int	limit_y;

	mini.ratio_y_player = (mini.start_y + y * mini.ratio_y);
	mini.ratio_x_player = (mini.start_x + x * mini.ratio_x);
	x_player = (int)mini.ratio_x_player - 3;
	x_backup = x_player;
	y_player = (int)mini.ratio_y_player - 3;
	limit_x = x_player + 6;
	limit_y = y_player + 6;
	while (y_player <= limit_y)
	{
		while (x_player <= limit_x)
			put_pixel(mlx.img, x_player++, y_player, 0x00FF00);
		x_player = x_backup;
		y_player++;
	}
}

void	put_minimap(t_mlx mlx, t_minimap minimap)
{
	put_player_minimap(mlx, 0, 0, minimap);
	mlx_put_image_to_window(mlx.init, mlx.window, minimap.img, minimap.start_x, minimap.start_y);
}

static inline void	init_minimap_colors(t_game *game,
		t_minimap mini, t_minimap copy)
{
	int		y;
	int		x;
	char	box_token;

	mini.end_x -= mini.start_x;
	y = mini.end_y - mini.start_y;
	while (y--)
	{
		x = mini.end_x;
		while (x--)
		{
			box_token = return_token_map(game->map, copy, y + mini.start_y, x + mini.start_x);
			if (box_token == '1' || box_token == ' '
				|| y == mini.start_y || y == mini.end_y
				|| x == mini.start_x || x == mini.end_x)
				put_pixel(mini.img, x, y, 0xff);
			else
				put_pixel(mini.img, x, y, 0x808080);
		}
	}
}

void	init_minimap(t_game *game)
{
	t_minimap	minimap;

	minimap.fract_of_h = WIN_HEIGHT / 20;
	minimap.start_y = minimap.fract_of_h;
	minimap.end_y = minimap.fract_of_h * 6;
	minimap.height_mini = minimap.end_y - minimap.start_y;
	minimap.fract_of_w = WIN_WIDTH / 20;
	minimap.end_x = WIN_WIDTH - minimap.fract_of_w;
	minimap.start_x = minimap.end_x - minimap.fract_of_w * 4;
	minimap.width_mini = minimap.end_x - minimap.start_x;
	minimap.ratio_y = (double)minimap.height_mini / ((double)game->map.h_map);
	minimap.ratio_x = (double)minimap.width_mini / ((double)game->map.w_map);
	minimap.img = mlx_new_image(game->mlx.init, minimap.end_x - minimap.start_x, minimap.end_y - minimap.start_y);
	init_minimap_colors(game, minimap, minimap);
	game->map.minimap = minimap;
}

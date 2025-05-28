/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by marvin            #+#    #+#             */
/*   Updated: 2025/05/28 20:17:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline char return_token_map(t_map map, int pos[2],
	int line_b[2], int col_b[3])
{
	int line;
	int col;
	double arr_map_ratio;

	arr_map_ratio = (double)line_b[2] / ((double)map.w_map + 1);
	line = (int)((pos[0] - line_b[0]) / arr_map_ratio);
	if (line > map.w_map)
		return ('0');
	arr_map_ratio = (double)col_b[2] / ((double)map.h_map - 1);
	col = (int)((pos[1] - col_b[0]) / arr_map_ratio);
	if (col > map.h_map)
		return ('0');
	return (map.map_array[line][col]);
}

static inline void	put_minimap_pixels(t_game game, int line_b[3],
	int col_b[3], double player_pos[2])
{
	int		y;
	int		x;
	char	box_token;

	y = line_b[0];
	while (y < line_b[1])
	{
		x = col_b[0];
		while (x < col_b[1])
		{
			box_token = return_token_map(game.map, (int[2]){y, x}, line_b,
				col_b);
			if ((int)player_pos[0] >= y - 3 && (int)player_pos[0] <= y + 3
				&& (int)player_pos[1] >= x - 3 && (int)player_pos[1] <= x + 3)
				put_pixel(game.mlx.img, x, y, 0x00FF00);
			else if (box_token == '1' || box_token == ' ' || y == line_b[0]
				|| y == line_b[1] - 1 || x == col_b[0] || x == col_b[1] - 1)
				put_pixel(game.mlx.img, x, y, 0x000000);
			else
				put_pixel(game.mlx.img, x, y, 0x808080);
			x++;
		}
		y++;
	}
}

void	display_minimap(t_game game)
{
	int		line_borders[3];
	int		col_borders[3];
	double	arr_map_ratio;
	double	player_pos[2];
	int		col_ratio;

	line_borders[0] = WIN_HEIGHT / 20;
	line_borders[1] = line_borders[0] * 6;
	line_borders[2] = line_borders[1] - line_borders[0];
	col_ratio = WIN_WIDTH / 20;
	col_borders[1] = WIN_WIDTH - col_ratio;
	col_borders[0] = col_borders[1] - col_ratio * 4;
	col_borders[2] = col_borders[1] - col_borders[0];
	arr_map_ratio = (double)line_borders[2] / ((double)game.map.w_map + 1);
	player_pos[0] = (line_borders[0] + game.player.y * arr_map_ratio);
	arr_map_ratio = (double)col_borders[2] / ((double)game.map.h_map - 1);
	player_pos[1] = (col_borders[0] + game.player.x * arr_map_ratio);
	put_minimap_pixels(game, line_borders, col_borders, player_pos);
	mlx_put_image_to_window(game.mlx.init, game.mlx.window, game.mlx.img, 0, 0);
}

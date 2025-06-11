/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/11 22:14:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	put_player_minimap(double x, double y, t_minimap mini)
{
	int	x_backup;
	int	x_player;
	int	y_player;
	int	limit_x;
	int	limit_y;

	mini.h_player = y * mini.ratio_h;
	mini.w_player = x * mini.ratio_w;
	x_player = (int)mini.w_player - 3;
	x_backup = x_player;
	y_player = (int)mini.h_player - 3;
	limit_x = x_player + 6;
	limit_y = y_player + 6;
	while (y_player <= limit_y)
	{
		while (x_player <= limit_x)
			put_pixel(mini.player_img, x_player++, y_player, OX_GREEN);
		x_player = x_backup;
		y_player++;
	}
}

void	put_minimap(t_mlx mlx, t_minimap mini, t_player player)
{
	mlx_put_image_to_window(mlx.init, mlx.window, mini.mini_img,
		mini.x_mini_img, mini.y_mini_img);
	mini.y_player_img = player.y * mini.ratio_h;
	mini.x_player_img = player.x * mini.ratio_w;
	put_player_minimap(player.x, player.y, mini);
	mlx_put_image_to_window(mlx.init, mlx.window, mini.player_img,
		mini.x_player_img, mini.y_player_img);
}

static inline char	return_token_map(t_map map, t_minimap mini, int y, int x)
{
	int	line;
	int	col;

	line = (int)(y / mini.ratio_y);
	if (line == map.h_map)
		return ('1');
	if (line > map.h_map)
		return ('0');
	col = (int)(x / mini.ratio_x);
	if (col > map.w_map)
		return ('0');
	if (line == map.w_map)
		return ('1');
	return (map.map_array[line][col]);
}

void	init_minimap(t_game *game, int y, int x, char box_token)
{
	t_minimap	mini;

	mini.y_mini_img = WIN_HEIGHT / 20;
	mini.x_mini_img = (WIN_WIDTH / 4) * 3;
	mini.height_mini = WIN_HEIGHT / 4;
	mini.width_mini = WIN_WIDTH / 5;
	mini.ratio_h = (double)mini.height_mini / ((double)game->map.h_map);
	mini.ratio_w = (double)mini.width_mini / ((double)game->map.w_map);
	mlx_new_image(mini.mini_img, mini.width_mini, mini.height_mini);
	mlx_new_image(mini.player_img, 7, 7);
	y = -1;
	while (++y < mini.height_mini)
	{
		x = -1;
		while (++x < mini.width_mini)
		{
			box_token = return_token_map(game->map, mini, y, x);
			if (box_token == '1' || box_token == ' ' || !y || !x
				|| y == mini.height_mini - 1 || x == mini.width_mini - 1)
				put_pixel(mini.img, x, y, OX_BLACK);
			else
				put_pixel(mini.img, x, y, OX_GREY);
		}
	}
	game->map.mini = mini;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/12 18:55:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_minimap(t_mlx mlx, t_minimap mini, t_player player)
{
	mlx_put_image_to_window(mlx.init, mlx.window, mini.mini_img,
		mini.x_mini_img, mini.y_mini_img);
	if (player.y < 1.4)
		mini.y_player_img = player.y * mini.ratio_h + mini.y_mini_img;
	else
		mini.y_player_img = player.y * mini.ratio_h - 3 + mini.y_mini_img;
	if (player.x < 1.4)
		mini.x_player_img = player.x * mini.ratio_w + mini.x_mini_img;
	else
		mini.x_player_img = player.x * mini.ratio_w - 3 + mini.x_mini_img;
	mlx_put_image_to_window(mlx.init, mlx.window, mini.player_img,
		mini.x_player_img, mini.y_player_img);
}

static inline char	return_token_map(t_map map, t_minimap mini, int y, int x)
{
	int	line;
	int	col;

	line = (int)(y / mini.ratio_h);
	if (line == map.h_map)
		return ('1');
	if (line > map.h_map)
		return ('0');
	col = (int)(x / mini.ratio_w);
	if (col > map.w_map)
		return ('0');
	if (col == map.w_map)
		return ('1');
	return (map.map_array[line][col]);
}

static void	put_player_minimap_pixels(t_minimap *mini, t_map map, int x, int y)
{
	char	box_token;

	y = -1;
	while (++y < mini->height_mini)
	{
		x = -1;
		while (++x < mini->width_mini)
		{
			box_token = return_token_map(map, *mini, y, x);
			if (box_token == '1' || box_token == ' ' || !y || !x
				|| y == mini->height_mini - 1 || x == mini->width_mini - 1)
				put_pixel(mini->mini_img, x, y, OX_BLACK);
			else
				put_pixel(mini->mini_img, x, y, OX_GRAY);
		}
	}
	y = -1;
	while (++y < 6)
	{
		x = 0;
		while (x < 6)
			put_pixel(mini->player_img, x++, y, OX_GREEN);
	}
}

void	init_minimap(t_minimap *mini, t_map map, t_mlx mlx)
{
	mini->y_mini_img = WIN_HEIGHT / 20;
	mini->x_mini_img = (WIN_WIDTH / 4) * 3;
	mini->height_mini = WIN_HEIGHT / 4;
	mini->width_mini = WIN_WIDTH / 5;
	mini->ratio_h = (double)mini->height_mini / ((double)map.h_map);
	mini->ratio_w = (double)mini->width_mini / ((double)map.w_map);
	mini->mini_img = mlx_new_image(mlx.init, mini->width_mini,
			mini->height_mini);
	mini->player_img = mlx_new_image(mlx.init, 6, 6);
	put_player_minimap_pixels(mini, map, 0, 0);
}

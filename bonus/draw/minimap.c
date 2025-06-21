/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/21 10:36:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_minimap(t_mlx mlx, t_minimap mini, t_player player)
{
	mlx_put_image_to_window(mlx.init, mlx.window, mini.mini_img,
		mini.x_mini_img, mini.y_mini_img);
	mlx_put_image_to_window(mlx.init, mlx.window, mini.player_img,
		player.x * mini.ratio_w - (mini.player_img_w / 2) + mini.x_mini_img,
		player.y * mini.ratio_h - (mini.player_img_h / 2) + mini.y_mini_img);
}

static inline int	return_token_map(t_map map, t_minimap mini, int y, int x)
{
	int	line;
	int	col;

	line = (int)(y / mini.ratio_h);
	if (line == map.h_map)
		return (1);
	if (line > map.h_map)
		return (0);
	col = (int)(x / mini.ratio_w);
	if (col > map.w_map)
		return (0);
	if (col == map.w_map)
		return (1);
	return (map.tiles[(int)map.map_array[line][col]].is_wall);
}

static void	put_player_minimap_pixels(t_minimap *mini, t_map map, int x, int y)
{
	y = -1;
	while (++y < mini->height_mini)
	{
		x = -1;
		while (++x < mini->width_mini)
		{
			if (return_token_map(map, *mini, y, x) || !y|| !x
				|| y == mini->height_mini - 1 || x == mini->width_mini - 1)
				put_pixel(mini->mini_img, x, y, OX_BLACK);
			else
				put_pixel(mini->mini_img, x, y, OX_GRAY);
		}
	}
	y = -1;
	while (++y < mini->player_img_h)
	{
		x = 0;
		while (x < mini->player_img_w)
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
	mini->player_img_w = 1;
	if (mini->player_img_w < mini->ratio_w)
		mini->player_img_w = mini->ratio_w;
	mini->player_img_h = 1;
	if (mini->player_img_h < mini->ratio_h)
		mini->player_img_h = mini->ratio_h;
	mini->player_img = mlx_new_image(mlx.init, mini->player_img_w, mini->player_img_h);
	put_player_minimap_pixels(mini, map, 0, 0);
}

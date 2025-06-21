/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/21 11:49:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_minimap(t_mlx mlx, t_minimap mini, t_player player)
{
	mlx_put_image_to_window(mlx.init, mlx.window, mini.mini_img,
		mini.x_mini_img, mini.y_mini_img);
	mlx_put_image_to_window(mlx.init, mlx.window, mini.player_img,
		player.x * mini.ratio_w - (mini.p_img_w / 2) + mini.x_mini_img,
		player.y * mini.ratio_h - (mini.p_img_h / 2) + mini.y_mini_img);
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
	while (++y < mini->h_mini)
	{
		x = -1;
		while (++x < mini->w_mini)
		{
			if (return_token_map(map, *mini, y, x) || !y|| !x
				|| y == mini->h_mini - 1 || x == mini->w_mini - 1)
				put_pixel(mini->mini_img, x, y, OX_BLACK);
			else
				put_pixel(mini->mini_img, x, y, OX_GRAY);
		}
	}
	y = -1;
	while (++y < mini->p_img_h)
	{
		x = 0;
		while (x < mini->p_img_w)
			put_pixel(mini->player_img, x++, y, OX_GREEN);
	}
}

void	init_minimap(t_minimap *mini, t_map map, t_mlx mlx)
{
	mini->y_mini_img = WIN_HEIGHT / 20;
	mini->x_mini_img = (WIN_WIDTH / 4) * 3;
	mini->limit_h_mini = WIN_HEIGHT / 3;
	mini->limit_w_mini = WIN_WIDTH / 5;
	mini->win_mini_ratio = mini->limit_h_mini / mini->limit_w_mini;
	map.win_ratio = (double)map.h_map / map.w_map;
	mini->h_mini = mini->limit_h_mini;
	mini->w_mini = mini->limit_w_mini;
	if (map.win_ratio < mini->win_mini_ratio)
		mini->h_mini = mini->w_mini * map.win_ratio;
	else if (map.win_ratio > mini->win_mini_ratio)
		mini->w_mini = mini->h_mini / map.win_ratio;
	mini->x_mini_img += mini->limit_w_mini - mini->w_mini;
	mini->ratio_h = (double)mini->h_mini / ((double)map.h_map);
	mini->ratio_w = (double)mini->w_mini / ((double)map.w_map);
	mini->mini_img = mlx_new_image(mlx.init, mini->w_mini, mini->h_mini);
	mini->p_img_w = 2;
	if (mini->p_img_w < mini->ratio_w)
		mini->p_img_w = mini->ratio_w;
	mini->p_img_h = 2;
	if (mini->p_img_h < mini->ratio_h)
		mini->p_img_h = mini->ratio_h;
	mini->player_img = mlx_new_image(mlx.init, mini->p_img_w, mini->p_img_h);
	put_player_minimap_pixels(mini, map, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:14 by marvin            #+#    #+#             */
/*   Updated: 2025/05/28 23:23:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline char	return_token_map(t_map map, t_minimap mini, int y, int x)
{
	int	line;
	int	col;

	line = (int)((y - mini.start_y_mini) / mini.ratio_y);
	if (line == map.h_map)
		return ('1');
	if (line > map.h_map)
		return ('0');
	col = (int)((x - mini.start_x_mini) / mini.ratio_x);
	if (col > map.w_map)
		return ('0');
	if (line == map.w_map)
		return ('1');
	return (map.map_array[line][col]);
}

static inline void	put_player_minimap(t_mlx mlx, int x, int y, t_minimap mini)
{
	int	x_backup;
	int	x_player;
	int	y_player;
	int	limit_x;
	int	limit_y;

	mini.ratio_y_player = (mini.start_y_mini + y * mini.ratio_y);
	mini.ratio_x_player = (mini.start_x_mini + x * mini.ratio_x);
	x_player = (int)mini.ratio_x_player - 3;
	x_backup = x_player;
	y_player = (int)mini.ratio_y_player - 3;
	limit_x = (int)mini.ratio_x_player + 3;
	limit_y = (int)mini.ratio_y_player + 3;
	while (y_player <= limit_y)
	{
		while (x_player <= limit_x)
			put_pixel(mlx.img, x_player++, y_player, 0x00FF00);
		x_player = x_backup;
		y_player++;
	}
}

void	put_minimap_pixels(t_mlx mlx, t_player player, t_minimap mini)
{
	int		i;
	int		y;
	int		x;

	i = 0;
	y = mini.start_y_mini;
	while (y < mini.end_y_mini)
	{
		x = mini.start_x_mini;
		while (x < mini.end_x_mini)
		{
			put_pixel(mlx.img, x, y, mini.color_str[i++]);
			x++;
		}
		y++;
	}
	put_player_minimap(mlx, player.x, player.y, mini);
	mlx_put_image_to_window(mlx.init, mlx.window, mlx.img, 0, 0);
}

void	init_minimap_colors(t_game *game, t_minimap mini)
{
	int		i;
	int		y;
	int		x;
	char	box_token;

	i = 0;
	y = mini.start_y_mini;
	while (y < mini.end_y_mini)
	{
		x = mini.start_x_mini;
		while (x < mini.end_x_mini)
		{
			box_token = return_token_map(game->map, mini, y, x);
			if (box_token == '1' || box_token == ' '
				|| y == mini.start_y_mini || y == mini.end_y_mini
				|| x == mini.start_x_mini || x == mini.end_x_mini)
				mini.color_str[i++] = 0;
			else
				mini.color_str[i++] = 0x808080;
			x++;
		}
		y++;
	}
}

void	init_minimap(t_game *game)
{
	t_minimap	minimap;

	minimap.fract_of_h = WIN_HEIGHT / 20;
	minimap.start_y_mini = minimap.fract_of_h;
	minimap.end_y_mini = minimap.fract_of_h * 6;
	minimap.height_mini = minimap.end_y_mini - minimap.start_y_mini;
	minimap.fract_of_w = WIN_WIDTH / 20;
	minimap.end_x_mini = WIN_WIDTH - minimap.fract_of_w;
	minimap.start_x_mini = minimap.end_x_mini - minimap.fract_of_w * 4;
	minimap.width_mini = minimap.end_x_mini - minimap.start_x_mini;
	minimap.ratio_y = (double)minimap.height_mini / ((double)game->map.h_map);
	minimap.ratio_x = (double)minimap.width_mini / ((double)game->map.w_map);
	minimap.color_str = malloc(sizeof(int)
			* (minimap.height_mini * minimap.width_mini));
	if (!minimap.color_str)
	{
		ft_error("fail init minimap color");
		return ;
	}
	init_minimap_colors(game, minimap);
	game->map.minimap = minimap;
}

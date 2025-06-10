/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_stats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:43 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/10 15:17:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	put_borders_hp_bar(t_img *bar, int hp_bar_w, int hp_bar_h)
{
	int	width;
	int	height;

	width = 0;
	while (width < hp_bar_w)
	{
		put_pixel(bar, width, 0, 0);
		put_pixel(bar, width, hp_bar_h, 0);
		width++;
	}
	height = 0;
	while (height < hp_bar_h)
	{
		put_pixel(bar, 0, height, 0);
		put_pixel(bar, hp_bar_w, height, 0);
		height++;
	}
}

static inline void	put_color_hp_bar(int hps_left, t_img *hp_bar, int hp_bar_w,
	int hp_bar_h)
{
	int	width;
	int	height;

	height = 1;
	width = 1;
	while (height < hp_bar_h - 1)
	{
		while (width < hp_bar_w - 1)
		{
			if (width > hps_left)
				put_pixel(hp_bar, width, height, 0xFF0000);
			else
				put_pixel(hp_bar, width, height, 0x00FF00);
			width++;
		}
		width = 1;
		height++;
	}
}

void	display_stats(t_stats p_stats, t_mlx mlx)
{
	double	hps_left;

	hps_left = p_stats.hp_bar_w / P_HPS * p_stats.hps;
	hps_left /= 2;
	put_borders_hp_bar(p_stats.hp_bar, p_stats.hp_bar_w, p_stats.hp_bar_h);
	put_color_hp_bar(hps_left, p_stats.hp_bar, p_stats.hp_bar_w,
		p_stats.hp_bar_h);
	mlx_put_image_to_window(mlx.init, mlx.window, p_stats.hp_bar,
		p_stats.start_w_hp, p_stats.start_h_hp);
}

void	init_hp_bar(t_stats *p_stats, t_mlx mlx)
{
	p_stats->start_h_hp = WIN_HEIGHT / 20;
	p_stats->start_w_hp = WIN_WIDTH / 20;
	p_stats->hp_bar_w = (WIN_WIDTH / 4) - p_stats->start_w_hp;
	p_stats->hp_bar_h = p_stats->start_h_hp / 2;
	p_stats->hp_bar = mlx_new_image(mlx.init, p_stats->hp_bar_w,
			p_stats->hp_bar_h);
}

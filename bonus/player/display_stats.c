/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_stats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:43 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/10 16:02:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	print_hp_bar(t_img *hp_bar, int *pixels_hp_bar,
	int hp_bar_h, int hp_bar_w)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	width = 0;
	height = 0;
	while (height < hp_bar_h)
	{
		while (width < hp_bar_w)
		{
			put_pixel(hp_bar, width, height, pixels_hp_bar[i++]);
			width++;
		}
		width = 0;
		height++;
	}
}

static inline void	put_pixels_hp_bar(int hps_left, t_stats *p_stats, int width,
	int height)
{
	int	i;

	i = 0;
	while (++width < p_stats->hp_bar_w)
		p_stats->pixels_hp_bar[i++] = 0;
	width = 1;
	while (height < p_stats->hp_bar_h - 1)
	{
		p_stats->pixels_hp_bar[i++] = 0;
		while (width < p_stats->hp_bar_w - 1)
		{
			if (width > hps_left)
				p_stats->pixels_hp_bar[i++] = 0xFF0000;
			else
				p_stats->pixels_hp_bar[i++] = 0x00FF00;
			width++;
		}
		p_stats->pixels_hp_bar[i++] = 0;
		width = 1;
		height++;
	}
	width = -1;
	while (++width < p_stats->hp_bar_w)
		p_stats->pixels_hp_bar[i++] = 0;
}

void	display_stats(t_stats p_stats, t_mlx mlx)
{
	double	hps_left;

	if (p_stats.hps != p_stats.old_hps)
	{
		hps_left = p_stats.hp_bar_w / P_HPS * p_stats.hps;
		hps_left /= 2;
		put_pixels_hp_bar(hps_left, &p_stats, 0, 1);
	}
	print_hp_bar(p_stats.hp_bar, p_stats.pixels_hp_bar,
		p_stats.hp_bar_h, p_stats.hp_bar_w);
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
	p_stats->pixels_hp_bar = malloc(sizeof(int)
			* (p_stats->hp_bar_h * p_stats->hp_bar_w));
	put_pixels_hp_bar(P_HPS, p_stats, -1, 1);
}

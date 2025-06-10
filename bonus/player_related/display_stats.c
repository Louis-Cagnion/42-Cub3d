/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_stats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:43 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/10 11:49:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	put_borders_h_bar(int start_h_bar[2], int end_h_bar[2])
{
	int width;
	int height;

	width = start_h_bar[1];
	while (width < start_h_bar[1])
	{
		put_pixel(mlx.img, width, start_h_bar[0], 0);
		put_pixel(mlx.img, width, start_h_bar[0], 0);
	}
	height = start_h_bar[0];
	while (height < start_h_bar[0])
	{
		put_pixel(mlx.img, width, start_h_bar[1], 0);
		put_pixel(mlx.img, width, start_h_bar[1], 0);
	}
}

static inline void	put_color_h_bar(int start_h_bar[2], int end_h_bar[2],
	int hps_left)
{
	int width;
	int height;

	height = start_hp_bar[0] + 1;
	width = start_hp_bar[1] + 1;
	while (height < end_hp_bar[0])
	{
		while (width < end_hp_bar[1])
		{
			if (width > hps_left)
				put_pixel(mlx.img, width, height, 0xFF0000);
			else
				put_pixel(mlx.img, width, height, 0x00FF00);
		}
	}
}

void	display_stats(t_stats p_stats, t_mlx mlx)
{
	int		start_hp_bar[2];
	int		end_hp_bar[2];
	double	hps_left;
	
	start_hp_bar[0] = WIN_HEIGHT / 20;
	start_hp_bar[1] = WIN_WIDTH / 20;
	end_hp_bar[0] = WIN_HEIGHT / 20 * 1.5;
	end_hp_bar[1] = WIN_WIDTH / 10;
	hps_left = ((end_hp_bar[1] - start_hp_bar[1]) / P_HPS * p_stats.hps)
				+ start_hp_bar[1];
	put_color_h_bar(start_hp_bar, end_hp_bar, hps_left);
	put_borders_h_bar(start_hp_bar, end_hp_bar);
}

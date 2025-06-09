/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:01:47 by marvin            #+#    #+#             */
/*   Updated: 2025/06/09 19:08:00 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = 1;

	(void)x;
	(void)y;
	return (1);
	if (game->key_infos.ctrl_key)
		return (0);
	if (x < last_x)
		game->player.rotation = -ROT_SPEED * 2;
	else if (x > last_x)
		game->player.rotation = ROT_SPEED * 2;
	if (x <= 10)
		mlx_mouse_move(game->mlx.init, game->mlx.window, WIN_WIDTH - 11, y);
	else if (x > (WIN_WIDTH - 10))
		mlx_mouse_move(game->mlx.init, game->mlx.window, 11, y);
	last_x = x;
	return (0);
}

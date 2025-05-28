/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:02:01 by locagnio          #+#    #+#             */
/*   Updated: 2025/05/21 17:43:16 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

inline void	update_player_ray_dirs(t_player *player)
{
	player->ray_dir_x[0] = player->direction_x - player->plane_x;
	player->ray_dir_x[1] = player->plane_x * 2;
	player->ray_dir_y[0] = player->direction_y - player->plane_y;
	player->ray_dir_y[1] = player->plane_y * 2;
	player->inv_deter = 1.0 / (player->plane_x * player->direction_y
			- player->direction_x * player->plane_y);
}

int	key_pressed_check_camera(t_player *player, t_keyboard_control key_infos)
{
	int		ret;
	double	rotation;
	double	temp;

	ret = key_infos.left_key - key_infos.right_key;
	if (ret)
	{
		rotation = -ROT_SPEED;
		if (ret >> 31)
			rotation = ROT_SPEED;
		temp = player->direction_x;
		player->direction_x = temp * cos(rotation)
			- player->direction_y * sin(rotation);
		player->direction_y = temp * sin(rotation)
			+ player->direction_y * cos(rotation);
		temp = player->plane_x;
		player->plane_x = temp * cos(rotation)
			- player->plane_y * sin(rotation);
		player->plane_y = temp * sin(rotation)
			+ player->plane_y * cos(rotation);
		update_player_ray_dirs(player);
	}
	return (ret);
}

void	key_pressed_check_controls(t_game *game, t_player *player)
{
	int		hsp;
	int		vsp;

	hsp = game->key_infos.d_key - game->key_infos.a_key;
	vsp = game->key_infos.s_key - game->key_infos.w_key;
	player->mvt_speed = SPEED;
	if (hsp && vsp)
		player->mvt_speed *= 0.7;
	if (hsp >> 31)
		actualise_player_pos(game->map.map_array, player, 'a');
	else if (hsp)
		actualise_player_pos(game->map.map_array, player, 'd');
	if (vsp >> 31)
		actualise_player_pos(game->map.map_array, player, 'w');
	else if (vsp)
		actualise_player_pos(game->map.map_array, player, 's');
}

/* for bonus */
/* mlx_mouse_hook(map->mlx.window, mouse_hook, mlx); */
/* int	mouse_hook(int button, int x, int y, t_map *map)
{
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		mouse_controls(button, x, y, mlx);
	return (0);
} */

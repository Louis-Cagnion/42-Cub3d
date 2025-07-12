/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:36:53 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/12 20:01:11 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline t_texture	get_texture(t_game *game,
		t_cast_infos *infos, double *wall_x, t_tile tiles)
{
	if (!infos->is_side)
	{
		*wall_x = game->player.y + infos->wall_dist * infos->ray_dir[1];
		return (tiles.tex_list[2 + (infos->ray_dir[0] < 0)]);
	}
	*wall_x = game->player.x + infos->wall_dist * infos->ray_dir[0];
	return (tiles.tex_list[infos->ray_dir[1] < 0]);
}

static inline void	draw_texture(int *addr, t_texture *tex,
	t_raycast *infos, int size_line)
{
	int		*data;
	int		*addr_two;
	double	tex_pos[2];
	double	step;
	int		tex_size_line;

	step = tex->d_height / infos->line_height;
	tex_pos[0] = (infos->wall_pos[0] - infos->consts->half_win_height
			+ infos->half_line_height - infos->cam_y) * step;
	infos->temp = ((infos->wall_pos[1] - infos->wall_pos[0]) >> 1) + 1;
	data = (int *)(tex->data + infos->texture_x);
	tex_size_line = tex->size_line >> 2;
	addr_two = addr + size_line * infos->wall_pos[1];
	tex_pos[1] = tex_pos[0] + (step * (infos->temp << 1));
	addr += size_line * infos->wall_pos[0];
	while (infos->temp--)
	{
		*addr = *(data + ((int)tex_pos[0] * tex_size_line));
		*addr_two = *(data + ((int)tex_pos[1] * tex_size_line));
		tex_pos[0] += step;
		tex_pos[1] -= step;
		addr += size_line;
		addr_two -= size_line;
	}
}

void	put_texture(t_game *game, int *addr, t_raycast *infos, int size_line)
{
	int			tex_x;
	double		wall_x;
	t_texture	tex;

	tex = get_texture(game, infos->cast_infos, &wall_x,
			game->map.tiles[infos->cast_infos->tile]);
	wall_x -= (int)wall_x;
	tex_x = wall_x * tex.d_width;
	if ((!infos->cast_infos->is_side && infos->cast_infos->ray_dir[0] > 0)
		|| (infos->cast_infos->is_side && infos->cast_infos->ray_dir[1] < 0))
		tex_x = tex.width - tex_x - 1;
	infos->texture_x = (tex.width - tex_x - 1) * tex.fake_bpp;
	draw_texture(addr, &tex, infos, size_line);
}

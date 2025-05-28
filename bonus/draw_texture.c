/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:36:53 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/19 17:25:41 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline t_texture	get_texture(t_game *game,
		t_raycast *infos, double *wall_x)
{
	if (!infos->side)
	{
		*wall_x = game->player.y + infos->wall_dist * infos->ray_dir[1];
		return (game->map.tex_list[2 + (infos->ray_dir[0] < 0)]);
	}
	*wall_x = game->player.x + infos->wall_dist * infos->ray_dir[0];
	return (game->map.tex_list[infos->ray_dir[1] < 0]);
}

// backup ((int)tex_pos & tex.tex_endian)
static inline void	draw_texture(int *addr, t_texture tex,
	t_raycast *infos, int size_line)
{
	void	*data;
	double	tex_pos;
	double	step;
	int		tex_size_line;
	int		y;

	step = tex.d_height / infos->line_height;
	tex_pos = (infos->wall_pos[0] - infos->half_win_height
			+ infos->half_line_height) * step;
	tex_size_line = tex.size_line;
	y = infos->wall_pos[1] - infos->wall_pos[0];
	data = tex.data + infos->texture_x;
	while (y--)
	{
		*addr = *(int *)(data + (int)tex_pos * tex_size_line);
		tex_pos += step;
		addr += size_line;
	}
}

void	put_texture(t_game *game, int *addr, t_raycast *infos, int size_line)
{
	int			tex_x;
	double		wall_x;
	t_texture	tex;

	tex = get_texture(game, infos, &wall_x);
	wall_x -= (int)wall_x;
	tex_x = (wall_x * tex.d_width);
	if ((!infos->side && infos->ray_dir[0] > 0)
		|| (infos->side && infos->ray_dir[1] < 0))
		tex_x = tex.width - tex_x - 1;
	infos->texture_x = (tex.width - tex_x - 1) * tex.fake_bpp;
	draw_texture(addr, tex, infos, size_line);
}

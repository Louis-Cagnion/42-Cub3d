/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:52:59 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/01 12:12:14 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	init_sprite_consts(t_sprite_drawing *spr,
		t_entity *entity, int half_win_height, int cam_y)
{
	int		half_height;
	int		screen_x;

	screen_x = entity->screen_x;
	half_height = entity->half_height;
	spr->delim_y_start = -half_height + half_win_height + cam_y;
	spr->delim_y_end = half_height + half_win_height + cam_y;
	spr->delim_x_start = -half_height + screen_x;
	if (spr->delim_x_start >> 31)
		spr->delim_x_start = 0;
	spr->delim_x_end = half_height + screen_x;
	if (spr->delim_x_end > WIN_WIDTH)
		spr->delim_x_end = WIN_WIDTH - 1;
	spr->screen_x = screen_x - half_height;
	spr->sprite_height = entity->sprite_height;
	spr->step = (double)entity->tex.height / entity->sprite_height;
	spr->ratio = entity->sprite_height / (double)entity->tex.height;
	spr->start_tex_y = (int)(spr->step * ((spr->delim_y_start << 8)
				- (WIN_HEIGHT << 7) + (spr->sprite_height << 7))) >> 8;
	spr->start_tex_y -= (--cam_y * spr->step);
	spr->screen_x = spr->delim_x_start - spr->screen_x;
}

static inline void	draw_sprite_stripe(t_sprite_drawing spr, int size_line,
		int tex_size_line, int height)
{
	int		*addr;
	int		*tex_addr;
	double	tex_y;
	double	step;

	tex_y = spr.tex_y;
	addr = spr.addr;
	tex_addr = spr.tex_addr;
	step = spr.step;
	while (height--)
	{
		*addr = *(tex_addr + (tex_size_line * (int)tex_y));
		tex_y += step;
		if (tex_y >= 1389)
			break ;
		addr += size_line;
	}
	return ;
}

static inline int	init_stripe_draw(t_sprite_drawing *spr, int *og_addr,
		int size_line, t_inv_size *zone)
{
	int		start_pix;
	int		end_pix;
	int		pix_skip_count;
	int		start_y;
	int		end_y;

	start_pix = zone->start;
	end_pix = zone->end;
	pix_skip_count = (int)(start_pix * spr->ratio);
	start_y = spr->delim_y_start + (int)((start_pix) * spr->ratio);
	end_y = spr->delim_y_start + (int)((end_pix) * spr->ratio);
	spr->tex_y = spr->start_tex_y + (spr->step * pix_skip_count);
	spr->addr = og_addr + (size_line * pix_skip_count);
	if (end_y >= WIN_HEIGHT)
		end_y = WIN_HEIGHT - 1;
	if (start_y >> 31)
	{
		spr->tex_y += spr->step * -start_y;
		spr->addr += size_line * -start_y;
		start_y = 0;
	}
	end_y -= start_y;
	if (--end_y >> 31)
		return (0);
	return (end_y);
}

static inline void	draw_sprite_loop(t_sprite_drawing spr, t_entity *temp_spr,
		int *og_addr, int size_line)
{
	int		tex_x;
	int		*tex_data;
	int		tex_size_line;
	int		height;
	t_list	*cur;

	tex_x = (int)(spr.screen_x * temp_spr->tex.width / spr.sprite_height);
	tex_data = (int *)temp_spr->tex.data;
	tex_data += tex_x;
	tex_size_line = temp_spr->tex.fake_size_line;
	cur = temp_spr->invisible_parts[tex_x];
	while (cur)
	{
		height = init_stripe_draw(&spr, og_addr, size_line,
				cur->data);
		spr.tex_addr = tex_data;
		draw_sprite_stripe(spr, size_line, tex_size_line, height);
		cur = cur->next;
	}
}

void	draw_sprites(t_raycast infos, t_game *game)
{
	t_sprite_drawing	spr;
	t_entity			*temp_spr;
	int					num_sprite;
	int					*addr;
	int					stripe;

	num_sprite = -1;
	temp_spr = (t_entity *)game->map.entity_list->data;
	spr.cam_y = infos.cam_y;
	while (++num_sprite < 1)
	{
		if (temp_spr->draw_dir_y <= 0)
			continue ;
		init_sprite_consts(&spr, temp_spr, infos.half_win_height, infos.cam_y);
		addr = (int *)(game->mlx.img->data + (spr.delim_y_start
					* infos.size_line << 2) + ((spr.delim_x_start) << 2));
		stripe = spr.delim_x_start;
		while (stripe < spr.delim_x_end)
		{
			if (infos.z_buffer[stripe++] > temp_spr->player_dist)
				draw_sprite_loop(spr, temp_spr, addr, infos.size_line);
			addr++;
			spr.screen_x++;
		}
	}
}

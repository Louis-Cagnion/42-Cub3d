/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:05:07 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/28 04:30:38 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	get_tex_pixel(t_texture tex, int x, int y)
{
	return (*(int *)(tex.data + (y * tex.size_line + (x << 2))));
}

static inline void	tex_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data + (y * img->size_line + (x << 2));
	*(int *)pixel = color;
}

static inline void	init_sprite_consts(t_sprite_drawing *spr, t_entity *entity, int half_win_height)
{
	int		half_height;
	int		screen_x;

	screen_x = entity->screen_x;
	half_height = entity->half_height;
	spr->delim_y_start = -half_height + half_win_height;
	spr->delim_y_end = half_height + half_win_height;
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
	spr->screen_x = spr->delim_x_start - spr->screen_x - 1;
}


void	draw_sprites(t_raycast infos, t_game *game)
{
	t_sprite_drawing spr;
	int		num_sprite;
	int		*addr;
	t_entity	*temp_spr;

	num_sprite = -1;
	temp_spr = (t_entity *)game->map.entity_list->data;
	while (++num_sprite < 1)
	{
		if (temp_spr->draw_dir_y <= 0)
			continue ;
		init_sprite_consts(&spr, temp_spr, infos.half_win_height);
		int		*temp_addr;
		double	texY;
		addr = (int *)(game->mlx.img->data + (spr.delim_y_start * infos.size_line << 2) + ((spr.delim_x_start - 1) << 2));
		for (int stripe = spr.delim_x_start; stripe < spr.delim_x_end; stripe++)
		{
			addr++;
			spr.screen_x++;
			if (infos.z_buffer[stripe] <= temp_spr->player_dist)
				continue ;
			int	tex_x = (int)(spr.screen_x * temp_spr->tex.width / spr.sprite_height);
			t_list *cur = temp_spr->invisible_parts[tex_x];
			while (cur)
			{
				int start_pix = ((t_inv_size *)(cur->data))->start;
				int end_pix = ((t_inv_size *)(cur->data))->end;
				int	pix_skip_count = (int)(start_pix * spr.ratio);
				int start_y = spr.delim_y_start + (int)(start_pix * spr.ratio);
				texY = spr.start_tex_y + (spr.step * pix_skip_count);
				temp_addr = addr + (infos.size_line * pix_skip_count);
				int end_y = spr.delim_y_start + (int)(end_pix * spr.ratio);
				if (end_y >= WIN_HEIGHT)
					end_y = WIN_HEIGHT - 1;
				if (start_y >> 31)
				{
					texY += spr.step * -start_y;
					temp_addr += infos.size_line * -start_y;
					start_y = 0;
				}
				for (int y = start_y; y < end_y; y++)
				{
					*temp_addr = get_tex_pixel(temp_spr->tex, tex_x, (int)texY);
					texY += spr.step; 
					temp_addr += infos.size_line;
				}
				cur = cur->next;
			}
		}
	}
}

static t_inv_size	*create_new_part(int start, int end)
{
	t_inv_size	*dest;

	dest = malloc(sizeof(t_inv_size));
	if (!dest)
		return (NULL);
	dest->start = start;
	dest->end = end;
	return (dest);
}

static int	go_to_next_pixel(int **addr_ref, int size_line, int height)
{
	int		*addr;
	int		count;

	addr = *addr_ref;
	count = 0;
	while (height--)
	{
		if (!(*addr >> 31))
		{
			*addr_ref = addr;
			return (count);
		}
		addr += size_line;
		count++;
	}
	*addr_ref = NULL;
	return (-height);
}

static t_list	*fill_invisible_stripe(t_entity *entity, int *addr, int size_line, int x)
{
	t_list	*lst;
	t_list	*dest;
	int		height;
	int		y;
	int		count;

	height = entity->tex.height;
	y = go_to_next_pixel(&addr, size_line, height);
	if (!addr)
		return (create_cell(create_new_part(height, height)));
	dest = create_cell(create_new_part(y, height)); 
	lst = dest;
	y--;
	while (++y < height)
	{
		count = y - 1;
		while (++count < height && !(*addr >> 31))
			addr += size_line;
		((t_inv_size *)(lst->data))->end = count;
		while ((count < height) && *addr >> 31)
		{
			addr += size_line;
			count++;
		}
		y = count;
		lst->next = create_cell(create_new_part(y--, height));
		lst = lst->next;
	}
	return (dest);
}

static void	fill_invisible_buffer(t_entity *entity)
{
	t_list	**buffer;
	int		*addr;
	int		size_line;
	int		x;

	buffer = entity->invisible_parts;
	x = -1;
	addr = (int *)entity->tex.data;
	size_line = entity->tex.size_line >> 2;
	while (++x < entity->tex.width)
		buffer[x] = fill_invisible_stripe(entity, addr++, size_line, x);
	buffer[x] = NULL;
}

t_entity	*create_entity(char *tex_path, double x, double y, void *mlx_ptr)
{
	t_entity	*dest;
	t_texture	tex;

	dest = malloc(sizeof(t_entity));
	dest->x = x;
	dest->y = y;
	tex.ptr = mlx_xpm_file_to_image(mlx_ptr, tex_path, &tex.width, &tex.height);
	if (tex.ptr)
		tex.data = mlx_get_data_addr(tex.ptr, &tex.bpp, &tex.size_line, &tex.endian);
	tex.tex_endian = tex.endian - 1;
	tex.d_width = (double)tex.width;
	tex.d_height = (double)tex.height;
	dest->tex = tex;
	dest->invisible_parts = malloc(sizeof(t_list *) * (tex.width + 1));
	fill_invisible_buffer(dest);
	return (dest);
}

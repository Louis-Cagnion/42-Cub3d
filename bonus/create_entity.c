/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:05:07 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/03 01:58:53 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static t_list	*fill_invisible_stripe(t_texture tex,
		int *addr, int size_line)
{
	t_list	*lst;
	t_list	*dest;
	int		height;
	int		y;

	height = tex.height;
	y = go_to_next_pixel(&addr, size_line, height);
	if (!addr)
		return (create_cell(create_new_part(height, height)));
	dest = create_cell(create_new_part(y--, height));
	lst = dest;
	while (++y < height)
	{
		y--;
		while (++y < height && !(*addr >> 31))
			addr += size_line;
		((t_inv_size *)(lst->data))->end = y--;
		while ((++y < height) && *addr >> 31)
			addr += size_line;
		lst->next = create_cell(create_new_part(y--, height));
		lst = lst->next;
	}
	return (dest);
}

t_sprite_frame	*create_sprite_frame(t_texture tex)
{
	t_sprite_frame	*dest;
	t_list			**buffer;
	int				*addr;
	int				size_line;
	int				x;

	dest = malloc(sizeof(t_sprite_frame));
	dest->tex = tex;
	dest->invisible_parts = malloc(sizeof(t_list *) * (tex.width + 1));
	buffer = dest->invisible_parts;
	x = -1;
	addr = (int *)tex.data;
	size_line = tex.size_line >> 2;
	while (++x < tex.width)
		buffer[x] = fill_invisible_stripe(tex, addr++, size_line);
	buffer[x] = NULL;
	return (dest);
}

t_entity	*create_entity(char *tex_path, double x, double y, void *mlx_ptr)
{
	t_entity		*dest;
	t_texture		tex;

	dest = malloc(sizeof(t_entity));
	dest->x = x;
	dest->y = y;
	tex.ptr = mlx_xpm_file_to_image(mlx_ptr, tex_path, &tex.width, &tex.height);
	if (tex.ptr)
		tex.data = mlx_get_data_addr(tex.ptr, &tex.bpp,
				&tex.size_line, &tex.endian);
	tex.tex_endian = tex.endian - 1;
	tex.d_width = (double)tex.width;
	tex.d_height = (double)tex.height;
	tex.fake_size_line = tex.size_line >> 2;
	dest->frame_list = create_cell(create_sprite_frame(tex));
	dest->first_frame = (void *)dest->frame_list;
	dest->cur_tex = tex;
	dest->cur_invisible_parts = ((t_sprite_frame *)dest->frame_list->data)
		->invisible_parts;
	dest->frame_list->next = dest->frame_list;
	dest->framerate = 24;
	dest->frame_count = 0;
	add_entity_frame(dest, "./assets/isaac.xpm", mlx_ptr);
	add_entity_frame(dest, "./assets/mario.xpm", mlx_ptr);
	return (dest);
}

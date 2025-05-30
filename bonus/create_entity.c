/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:05:07 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/28 15:54:09 by gakarbou         ###   ########.fr       */
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

static t_list	*fill_invisible_stripe(t_entity *entity,
		int *addr, int size_line)
{
	t_list	*lst;
	t_list	*dest;
	int		height;
	int		y;

	height = entity->tex.height;
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
		buffer[x] = fill_invisible_stripe(entity, addr++, size_line);
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
		tex.data = mlx_get_data_addr(tex.ptr, &tex.bpp,
				&tex.size_line, &tex.endian);
	tex.tex_endian = tex.endian - 1;
	tex.d_width = (double)tex.width;
	tex.d_height = (double)tex.height;
	tex.fake_size_line = tex.size_line / 4;
	dest->tex = tex;
	dest->invisible_parts = malloc(sizeof(t_list *) * (tex.width + 1));
	fill_invisible_buffer(dest);
	return (dest);
}

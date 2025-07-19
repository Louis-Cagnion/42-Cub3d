/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tex_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:55:25 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/19 20:15:03 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	remove_duplicates(t_list *cur)
{
	t_list	*temp;
	t_list	*prev;

	while (cur)
	{
		prev = cur;
		temp = cur->next;
		while (temp)
		{
			if (!ft_strcmp(cur->data, temp->data))
			{
				prev->next = temp->next;
				free(temp->data);
				free(temp);
				temp = prev->next;
			}
			else
			{
				prev = temp;
				temp = temp->next;
			}
		}
		cur = cur->next;
	}
}

static void	create_textures(t_list *names, t_list **tex, void *mlx)
{
	t_texture	*dest;

	while (names)
	{
		dest = malloc(sizeof(t_texture));
		dest->ptr = mlx_xpm_file_to_image(mlx, names->data, &dest->width,
				&dest->height);
		if (dest->ptr)
			dest->data = mlx_get_data_addr(dest->ptr, &dest->bpp,
					&dest->size_line, &dest->endian);
		dest->fake_bpp = dest->bpp >> 3;
		dest->fake_size_line = dest->size_line >> 2;
		dest->tex_endian = dest->endian - 1;
		dest->d_width = (double)dest->width;
		dest->d_height = (double)dest->height;
		ft_listadd_back(tex, create_cell(dest));
		names = names->next;
	}
}

static void	add_path_to_list(t_tile *cur, t_list **head)
{
	ft_lstadd_front(head, create_cell(ft_strdup(cur->no_path)));
	ft_lstadd_front(head, create_cell(ft_strdup(cur->so_path)));
	ft_lstadd_front(head, create_cell(ft_strdup(cur->we_path)));
	ft_lstadd_front(head, create_cell(ft_strdup(cur->ea_path)));
	if (cur->floor_path)
		ft_lstadd_front(head, create_cell(ft_strdup(cur->floor_path)));
	if (cur->ceil_path)
		ft_lstadd_front(head, create_cell(ft_strdup(cur->ceil_path)));
}

void	create_tex_structs(t_map *map, void *mlx)
{
	int		i;

	i = -1;
	while (++i < 256)
		if (map->tile_defined[i])
			add_path_to_list((t_tile *)&map->tiles[i], &map->name_lst);
	remove_duplicates(map->name_lst);
	create_textures(map->name_lst, &map->tex_ptr, mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:21:23 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/03 14:34:29 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	store_image(char *pathname, t_map *map, void *mlx_ptr, int i)
{
	t_texture	dest;

	dest.ptr = mlx_xpm_file_to_image(mlx_ptr, pathname, &dest.width,
			&dest.height);
	if (dest.ptr)
		dest.data = mlx_get_data_addr(dest.ptr, &dest.bpp,
				&dest.size_line, &dest.endian);
	dest.fake_bpp = dest.bpp / 8;
	dest.tex_endian = dest.endian - 1;
	dest.d_width = (double)dest.width;
	map->tex_list[i] = dest;
}

void	store_textures(t_map *map, void *mlx)
{
	map->tex_list = malloc(sizeof(t_texture) * 4);
	if (!map->tex_list)
		return ;
	store_image(map->no_path, map, mlx, 0);
	store_image(map->so_path, map, mlx, 1);
	store_image(map->we_path, map, mlx, 2);
	store_image(map->ea_path, map, mlx, 3);
}

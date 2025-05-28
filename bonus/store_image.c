/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:21:23 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/28 16:59:17 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	store_image(char *pathname, t_map *map, void *mlx_ptr, int i)
{
	t_texture	dest;

	dest.ptr = mlx_xpm_file_to_image(mlx_ptr, pathname, &dest.width,
			&dest.height);
	if (dest.ptr)
		dest.data = mlx_get_data_addr(dest.ptr, &dest.bpp,
				&dest.size_line, &dest.endian);
	dest.fake_bpp = dest.bpp >> 3;
	dest.tex_endian = dest.endian - 1;
	dest.d_width = (double)dest.width;
	dest.d_height = (double)dest.height;
	map->tex_list[i] = dest;
}

static void	rgb_to_image(t_map *map, int color, void *mlx_ptr, int i)
{
	t_texture	dest;

	dest.ptr = mlx_new_image(mlx_ptr, 1, 1);
	if (dest.ptr)
		dest.data = mlx_get_data_addr(dest.ptr, &dest.bpp,
				&dest.size_line, &dest.endian);
	dest.fake_bpp = dest.bpp / 8;
	dest.tex_endian = dest.endian - 1;
	dest.d_width = 1.0f;
	dest.d_height = 1.0f;
	dest.width = 1;
	dest.height = 1;
	*(int *)dest.data = color;
	map->tex_list[i] = dest;
}

void	store_textures(t_map *map, void *mlx)
{
	map->tex_list = malloc(sizeof(t_texture) * 6);
	if (!map->tex_list)
		return ;
	store_image(map->no_path, map, mlx, 0);
	store_image(map->so_path, map, mlx, 1);
	store_image(map->we_path, map, mlx, 2);
	store_image(map->ea_path, map, mlx, 3);
	if (map->floor_path)
		store_image(map->floor_path, map, mlx, 4);
	else
		rgb_to_image(map, map->f_rgb, mlx, 4);
	if (map->ceil_path)
		store_image(map->ceil_path, map, mlx, 5);
	else
		rgb_to_image(map, map->c_rgb, mlx, 5);
}

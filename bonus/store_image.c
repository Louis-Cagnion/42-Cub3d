/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:21:23 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/08 21:35:15 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	rgb_to_image(t_tile *tile, int color, void *mlx_ptr, int i)
{
	t_texture	dest;

	dest.ptr = mlx_new_image(mlx_ptr, 1, 1);
	if (dest.ptr)
		dest.data = mlx_get_data_addr(dest.ptr, &dest.bpp,
				&dest.size_line, &dest.endian);
	dest.fake_bpp = dest.bpp / 8;
	dest.fake_size_line = dest.size_line >> 2;
	dest.tex_endian = dest.endian - 1;
	dest.d_width = 1.0f;
	dest.d_height = 1.0f;
	dest.width = 1;
	dest.height = 1;
	*(int *)dest.data = color;
	tile->tex_list[i] = dest;
}

static void	store_image(char *pathname, t_tile *tile, void *mlx_ptr, int i)
{
	t_texture	dest;

	if (i == 4 && !tile->floor_path)
	{
		rgb_to_image(tile, tile->f_rgb, mlx_ptr, 4);
		return ;
	}
	else if (i == 5 && !tile->ceil_path)
	{
		rgb_to_image(tile, tile->c_rgb, mlx_ptr, 5);
		return ;
	}
	dest.ptr = mlx_xpm_file_to_image(mlx_ptr, pathname, &dest.width,
			&dest.height);
	if (dest.ptr)
		dest.data = mlx_get_data_addr(dest.ptr, &dest.bpp,
				&dest.size_line, &dest.endian);
	dest.fake_bpp = dest.bpp >> 3;
	dest.fake_size_line = dest.size_line >> 2;
	dest.tex_endian = dest.endian - 1;
	dest.d_width = (double)dest.width;
	dest.d_height = (double)dest.height;
	tile->tex_list[i] = dest;
}

static void	store_defaults_settings(t_map *map, void *mlx)
{
	t_tile	*cur;
	t_tile	src;

	src = map->tiles[0];
	cur = &map->tiles['0'];
	cur->tex_list = malloc(sizeof(t_texture) * 6);
	if (src.floor_path)
		cur->floor_path = ft_strdup(src.floor_path);
	if (src.ceil_path)
		cur->ceil_path = ft_strdup(src.ceil_path);
	store_image(src.floor_path, cur, mlx, 4);
	store_image(src.ceil_path, cur, mlx, 5);
	cur = &map->tiles['1'];
	cur->tex_list = malloc(sizeof(t_texture) * 6);
	store_image(src.no_path, cur, mlx, 0);
	store_image(src.so_path, cur, mlx, 1);
	store_image(src.we_path, cur, mlx, 2);
	store_image(src.ea_path, cur, mlx, 3);
	cur->is_wall = 1;
}

static void	store_tile_texture(t_tile *cur, void *mlx, t_texture default_tex)
{
	cur->tex_list = malloc(sizeof(t_texture) * 6);
	if (cur->is_wall_str)
	{
		free(cur->is_wall_str);
		cur->is_wall = 1;
		store_image(cur->no_path, cur, mlx, 0);
		store_image(cur->so_path, cur, mlx, 1);
		store_image(cur->we_path, cur, mlx, 2);
		store_image(cur->ea_path, cur, mlx, 3);
		cur->tex_list[4] = default_tex;
		cur->tex_list[5] = default_tex;
	}
	else
	{
		cur->tex_list[0] = default_tex;
		cur->tex_list[1] = default_tex;
		cur->tex_list[2] = default_tex;
		cur->tex_list[3] = default_tex;
		store_image(cur->floor_path, cur, mlx, 4);
		store_image(cur->ceil_path, cur, mlx, 5);
	}
}

void	store_textures(t_map *map, void *mlx, t_game *game)
{
	t_tile		*cur;
	int			i;

	game->default_tex = create_default_texture(mlx);
	if (map->tile_defined[0])
	{
		store_defaults_settings(map, mlx);
		return ;
	}
	i = 256;
	while (--i)
	{
		if (!map->tile_defined[i])
			continue ;
		cur = &map->tiles[i];
		store_tile_texture(cur, mlx, game->default_tex);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:21:23 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/26 15:51:07 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	store_image(char *pathname, t_map *map, t_tile *tile, int i)
{
	t_list		*names;
	t_list		*textures;
	t_texture	dest;

	names = map->name_lst;
	textures = map->tex_ptr;
	dest = *(t_texture *)textures->data;
	while (names)
	{
		if (!ft_strcmp(names->data, pathname))
		{
			dest = *(t_texture *)textures->data;
			break ;
		}
		names = names->next;
		textures = textures->next;
	}
	tile->tex_list[i] = dest;
}

static void	store_defaults_settings(t_map *map,
		t_texture default_tex)
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
	store_image(src.floor_path, map, cur, 4);
	store_image(src.ceil_path, map, cur, 5);
	cur = &map->tiles['1'];
	cur->tex_list = malloc(sizeof(t_texture) * 6);
	store_image(src.no_path, map, cur, 0);
	store_image(src.so_path, map, cur, 1);
	store_image(src.we_path, map, cur, 2);
	store_image(src.ea_path, map, cur, 3);
	cur->tex_list[4] = default_tex;
	cur->tex_list[5] = default_tex;
	cur->is_wall = 1;
}

static void	store_tile_texture(t_tile *cur, t_map *map, t_texture default_tex)
{
	cur->tex_list = malloc(sizeof(t_texture) * 6);
	if (cur->is_wall_str)
	{
		cur->is_wall = ft_atod(cur->is_wall_str);
		free(cur->is_wall_str);
	}
	store_image(cur->no_path, map, cur, 0);
	store_image(cur->so_path, map, cur, 1);
	store_image(cur->we_path, map, cur, 2);
	store_image(cur->ea_path, map, cur, 3);
	store_image(cur->floor_path, map, cur, 4);
	store_image(cur->ceil_path, map, cur, 5);
}

void	store_textures(t_map *map, void *mlx, t_game *game)
{
	t_tile		*cur;
	int			i;

	game->default_tex = create_default_texture(mlx);
	create_tex_structs(map, mlx);
	if (map->tile_defined[0])
	{
		store_defaults_settings(map, game->default_tex);
		return ;
	}
	i = 256;
	while (--i)
	{
		if (!map->tile_defined[i])
			continue ;
		cur = &map->tiles[i];
		store_tile_texture(cur, map, game->default_tex);
	}
}

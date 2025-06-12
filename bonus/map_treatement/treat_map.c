/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:47:09 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/11 23:26:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	row_has_only_walls(char *row, t_tile tiles[256])
{
	int		i;

	i = -1;
	while (row[++i])
		if ((row[i] != 32) && !tiles[(int)row[i]].is_wall_str)
			return (0);
	return (1);
}

int	map_has_valid_tiles(char *map, char defined[256])
{
	int		i;

	i = -1;
	while (map[++i])
	{
		if (ft_strchr("\n\r ", map[i]))
			continue ;
		if (!defined[(int)map[i]])
			return (1);
	}
	return (0);
}

static char	*formated_map(char **map_array, t_map *map, int *len_strings, int i)
{
	char	*formated_map;
	int		j;

	map->w_map = ft_max_array(len_strings, map->h_map);
	while (map_array[++i])
	{
		if (len_strings[i] < map->w_map)
			map_array[i] = ft_realloc(map_array[i], map->w_map);
		j = -1;
		while (++j < map->w_map)
			if (map_array[i][j] == ' ' || map_array[i][j] == 0)
				map_array[i][j] = '1';
	}
	free(len_strings);
	map->map_array = map_array;
	formated_map = malloc(sizeof(char) * (map->h_map * map->w_map + 1));
	if (!formated_map)
		return (ft_error("Failed creating formated map.\n"), NULL);
	i = -1;
	while (map_array[++i])
		ft_memcpy(formated_map + (i * map->w_map), map_array[i], map->w_map);
	formated_map[i * map->w_map] = 0;
	return (formated_map);
}

/* check the sides of map to see if it's well bordered */
static int	check_sides(char **map_array, int map_height,
		int *len_strings, t_tile tiles[256])
{
	int	j;

	j = 1;
	while (j < map_height)
	{
		if ((map_array[j][0] != ' ')
			&& !tiles[(int)map_array[j][0]].is_wall_str)
			return (0);
		if ((map_array[j][len_strings[j] - 1] != ' ')
				&& !tiles[(int)map_array[j][len_strings[j] - 1]].is_wall_str)
			return (0);
		j++;
	}
	return (1);
}

int	treat_map(char *map, int i, t_game *game)
{
	char	**map_array;
	int		*len_strs;

	if (map_has_valid_tiles(map, game->map.tile_defined))
		return (ft_error("Invalid tiles used.\n"), 1);
	map_array = ft_split(map, "\n\r");
	if (!map_array)
		return (ft_error("Failed splitting map.\n"), 1);
	game->map.h_map = ft_count_words(map_array);
	len_strs = malloc(sizeof(int) * game->map.h_map);
	if (!len_strs)
		return (free_array(&map_array),
			ft_error("Failed getting len of strings.\n"), 1);
	while (map_array[++i])
		len_strs[i] = ft_strlen(map_array[i]);
	if (!row_has_only_walls(map_array[0], game->map.tiles)
		|| !row_has_only_walls(map_array[game->map.h_map - 1], game->map.tiles)
		|| !check_sides(map_array, game->map.h_map, len_strs, game->map.tiles)
		|| !check_limits(map_array, game->map.h_map, len_strs, game->map.tiles))
		return (free(len_strs), free_array(&map_array),
			ft_error("Invalid map.\n"), 1);
	game->map.map = formated_map(map_array, &game->map, len_strs, -1);
	if (!only_one_player(game))
		return (free_array(&map_array), 1);
	return (0);
}

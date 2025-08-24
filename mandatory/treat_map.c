/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:47:09 by locagnio          #+#    #+#             */
/*   Updated: 2025/08/24 19:49:25 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/* check the 9 boxs around a space and see if it's surrounded with 1 or spaces*/
static int	walls_around(int *len_strings, char **map_array, int i, int j)
{
	if ((map_array[j + 1] && i < len_strings[j + 1]
			&& !ft_strchr("1 ", map_array[j + 1][i]))
	|| (map_array[j + 1] && i + 1 < len_strings[j + 1]
		&& !ft_strchr("1 ", map_array[j + 1][i + 1]))
	|| (map_array[j + 1] && i > 0 && i - 1 < len_strings[j + 1]
		&& !ft_strchr("1", map_array[j + 1][i - 1]))
	|| (j > 0 && i < len_strings[j - 1]
		&& !ft_strchr("1 ", map_array[j - 1][i]))
	|| (j > 0 && i + 1 < len_strings[j - 1]
		&& !ft_strchr("1 ", map_array[j - 1][i + 1]))
	|| (j > 0 && i > 0 && i - 1 < len_strings[j - 1]
		&& !ft_strchr("1 ", map_array[j - 1][i - 1]))
	|| (map_array[j][i] && map_array[j][i + 1]
		&& !ft_strchr("1 ", map_array[j][i + 1]))
	|| (i > 0
		&& !ft_strchr("1 ", map_array[j][i - 1])))
		return (0);
	return (1);
}

/* if a space is not surrounded by the limits of the map, it return 0 */
static int	check_limits(char **map_array, int map_height, int *len_strings)
{
	int	i;
	int	j;

	j = 0;
	while (j < map_height)
	{
		i = 0;
		while (map_array[j][i])
		{
			if (map_array[j][i] == ' '
				&& !walls_around(len_strings, map_array, i, j))
				return (0);
			i++;
			if (!map_array[j][i] && !walls_around(len_strings, map_array, i, j))
				return (0);
		}
		j++;
	}
	return (1);
}

/* check the sides of map to see if it's well bordered */
static int	check_sides(char **map_array, int map_height, int *len_strings)
{
	int	j;

	j = 1;
	while (j < map_height)
	{
		if (!ft_strchr("1 ", map_array[j][0])
			|| !ft_strchr("1 ", map_array[j][len_strings[j] - 1]))
			return (0);
		j++;
	}
	return (1);
}

int	treat_map(char *map, int i, t_game *game)
{
	char	**map_array;
	int		*len_strings;

	if (!ft_str_isformat(map, "01NSEW \n\r"))
		return (ft_error("Wrong format used.\n"), 1);
	map_array = ft_split(map, "\n\r");
	if (!map_array)
		return (ft_error("Failed splitting map.\n"), 1);
	game->map.h_map = ft_count_words(map_array);
	len_strings = malloc(sizeof(int) * game->map.h_map);
	if (!len_strings)
		return (free_array(&map_array),
			ft_error("Failed getting len of strings.\n"), 1);
	while (map_array[++i])
		len_strings[i] = ft_strlen(map_array[i]);
	if (!ft_str_isformat(map_array[0], "1 ")
		|| !ft_str_isformat(map_array[game->map.h_map - 1], "1 ")
		|| !check_sides(map_array, game->map.h_map, len_strings)
		|| !check_limits(map_array, game->map.h_map, len_strings))
		return (free(len_strings), free_array(&map_array),
			ft_error("Invalid map.\n"), 1);
	game->map.map = formated_map(map_array, &game->map, len_strings, -1);
	if (!only_one_player(game))
		return (free_array(&map_array), 1);
	return (0);
}

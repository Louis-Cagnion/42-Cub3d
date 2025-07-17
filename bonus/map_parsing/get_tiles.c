/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:51:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/17 20:21:25 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	tile_already_defined(unsigned char token)
{
	int		a;

	if (!ft_strchr("NSWE", (char)token))
	{
		a = write(2, "Error\nTile '", 12);
		a += write(2, &token, 1);
		a += write(2, "' already defined\n", 18);
	}
	else
		a = write(2, "Error\nPlayer orientation cannot be a tile\n", 42);
	return (a * 0);
}

static int	get_tile_loop(char *content, int *i, char *elems[], t_map *map)
{
	char			*tile_content;
	unsigned char	token;
	int				save;

	while (ft_strchr("\n\t ", content[*i]))
		(*i)++;
	if (!ft_strchr(" \t{", content[*i + 1]))
		return (1);
	token = content[(*i)++];
	if (map->tile_defined[token])
		return (tile_already_defined(token));
	while (ft_strchr("\t ", content[*i]))
		(*i)++;
	if (content[*i] != '{')
		return (ft_error("Missing opening brace"), 0);
	save = ++(*i);
	while (ft_strncmp("\n}", content + *i, 2))
		(*i)++;
	tile_content = ft_strndup(content + save, *i - save);
	if (!check_elems(tile_content, elems, &map->tiles[token]))
		return (free(tile_content), 0);
	*i += 2;
	map->tile_defined[token] = 1;
	return (free(tile_content), 2);
}

int	get_tiles(char *content, int *i, char *elems[], t_map *map)
{
	int		save;

	while (ft_strchr("\n\t ", content[*i]))
		(*i)++;
	if (!ft_strchr(" \t", content[*i + 1]))
	{
		map->tile_defined['0'] = 1;
		map->tile_defined['1'] = 1;
		map->tile_defined[0] = 1;
		map->tiles['1'].is_wall_str = "";
		return (check_single_elem(content + *i, i, elems, &map->tiles[0]));
	}
	while (content[*i])
	{
		save = get_tile_loop(content, i, elems, map);
		if (!save)
			return (0);
		else if (save == 1)
			return (1);
	}
	return (1);
}

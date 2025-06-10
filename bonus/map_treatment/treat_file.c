/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:47:09 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/02 12:04:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_elem_infos(char *elems[])
{
	elems[0] = "NO";
	elems[1] = "SO";
	elems[2] = "WE";
	elems[3] = "EA";
	elems[4] = "F";
	elems[5] = "C";
	elems[6] = "W";
}

static inline void	define_player_tile(char *defined, char n)
{
	defined['N'] = n;
	defined['S'] = n;
	defined['W'] = n;
	defined['E'] = n;
}

int	treat_file(char *map_name, t_game *game)
{
	char	*file_infos;
	char	*elems[7];
	int		i;

	i = 0;
	init_elem_infos(elems);
	define_player_tile(game->map.tile_defined, 1);
	file_infos = ft_read_file(map_name);
	if (!file_infos || !file_infos[0])
		return (ft_error("Empty file.\n"), 1);
	if (!get_tiles(file_infos, &i, elems, &game->map))
		return (free(file_infos), 1);
	while (file_infos[i] && !ft_strchr("01NSEW ", file_infos[i]))
		i++;
	if (!file_infos[i])
	{
		free(file_infos);
		return (ft_error("No map given.\n"), 1);
	}
	if (treat_map(file_infos + i, -1, game))
		return (1);
	free(file_infos);
	define_player_tile(game->map.tile_defined, 0);
	return (!game->map.map || !game->map.map_array);
}
